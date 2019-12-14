#include "map.hpp"
#include "tinyxml2.hpp"

static double GRAD_CIRCLE = 360; // в градусах

side_object::side_object() 
    : radius{15}
    , mass{1}
{
    pos.fill(0);
}

car::car(): car(car_type::medium) {}

car::car(car_type type) {
    pos.fill(0);
    speed = 0;
    switch (type) {
        case car_type::small: {
            radius = 30;
            mass = 1;
            num_side_objects = 1;
            num_accelerations = 1;
            max_speed = 30;
            break;
        }
        case car_type::big: {
            radius = 30;
            mass = 3;
            num_side_objects = 3;
            num_accelerations = 3;
            max_speed = 30;
            break;
        }
        default: { // medium
            radius = 30;
            mass = 2;
            num_side_objects = 2;
            num_accelerations = 2;
            max_speed = 30;
        }
    }
}

double car::dist(const position& p) {
    return sqrt(pow((pos[0] - p[0]), 2) + pow((pos[1] - p[1]), 2)); 
}

game_map::game_map() {
    num_circle.fill(-1);
    load_map("default_maps/map.tmx");
}

bool game_map::load_map(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        std::cout << "not found map" << std::endl;
        return false;
    }
    
    tinyxml2::XMLElement* map_xml = doc.FirstChildElement("map");
    if (!map_xml) {
        return false;
    }
    size_t map_width = map_xml->IntAttribute("width", 0);
    size_t map_height = map_xml->IntAttribute("height", 0);
    double block_width = map_xml->IntAttribute("tilewidth", 0);
    double block_height = map_xml->IntAttribute("tileheight", 0);
    
    start_pos = {3830, 7320, 0}; // TODO: из файла (Рома)
    road_width = 440;
    
    std::cout << "map_width " << map_width << " map_height " << map_height << std::endl;

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    for (size_t col = 0; col < map_height; ++col) {
        std::vector<map_block> block_line(map_width);
        for (size_t row = 0; row <  map_width; ++row) {
            map_block& block = block_line[row];
            block.type = static_cast<map_block::block_type>(tile_xml->IntAttribute("gid", 1));
            block.pos = {row * block_width, col * block_height, block_width, block_height};
            tile_xml = tile_xml->NextSiblingElement("tile");
        }
        map_info.emplace_back(std::move(block_line));
    }
    
    return true;
}

void game_map::set_start_pos() {
    // TODO: направление стартовой позиции по х и у
    double dist = 60;
    position pos = start_pos;
    
    for (size_t idx = 0; idx < MAX_USERS; idx += 2) {
        pos[0] += 2 * dist;
        if (idx + 1 < MAX_USERS) {
            pos[1] += dist;
            players[idx].pos = pos;
            pos[1] -= 2 * dist;
            players[idx + 1].pos = pos;
            pos[1] += dist;
        } else {
            players[idx].pos = pos;
        }
    }
}

players_position game_map::get_players_pos() const {
    players_position pos;
    for (size_t idx = 0; idx < pos.size(); ++idx) {
        pos[idx] = players[idx].pos;
    }
    return pos;
}

// TODO:
players_rating game_map::get_rating() const {
    return players_rating();   
}

std::vector<position> game_map::get_side_objects_pos() const {
    std::vector<position> pos(side_objects.size());
    for (size_t idx = 0; idx < side_objects.size(); ++idx) {
        pos[idx] = side_objects[idx].pos;
    }
    return pos;
}

int8_t game_map::get_num_circle(size_t id) const {
    return num_circle[id];
}
    
void game_map::set_car(size_t id, car_type type) {
    players[id] = car(type);
}

void game_map::set_command(size_t id, const move_command& comm) {
    command[id] = comm;
}

void game_map::check_collision(size_t id) {
    // врезание машинок
    //bool has_collision = true;
    //while (has_collision) {
        //has_collision = false;
        //for (size_t i = 0; i < MAX_USERS; ++i) {
            car& player1 = players[id];
            double rad_angle = player1.pos[2] * 2. * M_PI / GRAD_CIRCLE;
            
            for (size_t idx = 0/*i + 1*/; idx < MAX_USERS; ++idx) {
                if (idx == id) {
                    continue;
                }
                car& player2 = players[idx];
                double dist = player1.dist(player2.pos) - (player1.radius + player2.radius); 
                if (dist < 1e-4) {
                    std::cout << "(map) fix collision" << std::endl << std::flush;
                    
                    player1.pos[0] -= 0.5 * dist * cos(rad_angle);
                    player1.pos[1] -= 0.5 * dist * sin(rad_angle);
                    
                    //rad_angle = player2.pos[2] * 2. * M_PI / GRAD_CIRCLE;
                    player2.pos[0] += 0.5 * dist * cos(rad_angle);
                    player2.pos[1] += 0.5 * dist * sin(rad_angle);
                    //player2.pos[2] = -player1.pos[2];
                    
                    player1.speed = 0.5 * (player1.speed + player2.speed);
                    player2.speed = player1.speed;
                    
                    //has_collision = true;
                }
            }
            
            //for (size_t i = 0; i < map_info.size();  )
            // TODO: выезд за трассу
        //}
        
    //}
}

void game_map::make_move() {
    double a = 1;
    
    for (size_t idx = 0; idx < MAX_USERS; ++idx) {
        car& player = players[idx];
        move_command& comm = command[idx];
        
        if (comm.back) {
            double next_speed = player.speed + a;
            player.speed = next_speed < player.max_speed ? next_speed : player.max_speed;
        } else if (comm.forward) {
            double next_speed = player.speed - a;
            player.speed = -next_speed < player.max_speed ? next_speed : -player.max_speed;
        } else if (fabs(player.speed) > 1e-7) { // inertion move
            int8_t sign = player.speed > 1e-7 ? 1 : -1;
            player.speed -= sign * a / 2.;
        } else {
            player.speed = 0;
        }
        
        double& angle = player.pos[2]; // в градусах
        if (command[idx].right_turn && fabs(player.speed) > 2.) {
            angle += 4;
        }
        if (command[idx].left_turn && fabs(player.speed) > 2.) {
            angle -= 4;
        }
        
        if (fabs(angle) > GRAD_CIRCLE) {
            int8_t sign = angle > GRAD_CIRCLE ? 1 : -1;
            angle -= sign * GRAD_CIRCLE;
        }
        
        double rad_angle = angle * 2. * M_PI / GRAD_CIRCLE;
        player.pos[0] += player.speed * cos(rad_angle);
        player.pos[1] += player.speed * sin(rad_angle);
        
        check_collision(idx);
        // std::cout << "v = " << player.speed << std::endl << std::flush;
        // std::cout << "angle = " << angle << " cos(angle) = " << cos(angle) << " sin(angle) = " << sin(angle) << std::endl << std::flush; 
        // comm = move_command();
    }
    
}
