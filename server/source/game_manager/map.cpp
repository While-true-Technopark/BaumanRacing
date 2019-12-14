#include "map.hpp"
#include "tinyxml2.hpp"

static double GRAD_CIRCLE = 360; // в градусах

side_object::side_object() 
    : radius{15}
    , mass{1}
{
    pos.fill(0);
}

game_object::game_object()
    : game_object(game_object_type::medium)
{}

game_object::game_object(game_object_type type) {
    pos.fill(0);
    speed = 0;
    switch (type) {
        case game_object_type::small: {
            radius = 30;
            mass = 1;
            num_side_objects = 1;
            num_accelerations = 1;
            max_speed = 30;
            break;
        }
        case game_object_type::big: {
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

double game_object::dist(const position& p) {
    return sqrt(pow((pos[0] - p[0]), 2) + pow((pos[1] - p[1]), 2)); 
}

game_map::game_map(size_t num_players)
    : players(num_players)
    , num_circle(num_players, -1)
    , command(num_players)
{
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
    h_x = map_xml->IntAttribute("tilewidth", 0);
    h_y = map_xml->IntAttribute("tileheight", 0);
    
    start_pos = {3830, 7320, 0}; // TODO: из файла (Рома)
    road_width = 440;
    
    std::cout << "map_width " << map_width << " map_height " << map_height << std::endl;

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    for (size_t i = 0; i < map_height; ++i) {
        std::vector<map_block> block_line(map_width);
        for (size_t j = 0; j <  map_width; ++j) {
            map_block& block = block_line[j];
            block.type = static_cast<map_block::block_type>(tile_xml->IntAttribute("gid", 1));
            block.pos = {j * h_x, i * h_y, h_x, h_y};
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
    
    for (size_t idx = 0; idx < players.size(); idx += 2) {
        pos[0] += 2 * dist;
        if (idx + 1 < players.size()) {
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
    
void game_map::set_setting(size_t id, game_object_type type) {
    players[id] = game_object(type);
}

void game_map::set_setting(size_t id, const move_command& comm) {
    command[id] = comm;
}

void game_map::check_collision(size_t id) {
    game_object& player1 = players[id];
    double rad_angle = player1.pos[2] * 2. * M_PI / GRAD_CIRCLE;
    size_t idx_x = player1.pos[0] / h_x;
    size_t idx_y = player1.pos[1] / h_y;
    map_block::block_type type = map_info[idx_x][idx_y].type;
    std::cout << "(map) block_type: " << type << std::endl << std::flush;
    if (type == map_block::wall || type == map_block::grass) {
    	//int8_t sign = player1.speed > 1e-7 ? 1 : -1;
    	//player1.pos[0] -= sign * 0.1 * player1.radius * cos(rad_angle);
    	player1.pos[0] -= 0.5 * player1.speed * cos(rad_angle);
        player1.pos[1] -= 0.5 * player1.speed * sin(rad_angle);
        player1.speed = 0;
        //command[id] = move_command();
    }
            
    for (size_t idx = 0; idx < players.size(); ++idx) {
        if (idx == id) {
            continue;
        }
        game_object& player2 = players[idx];
        double dist = player1.dist(player2.pos) - (player1.radius + player2.radius); 
        if (dist < 1e-4) {
            //int8_t sign = player1.speed > 1e-7 ? 1 : -1;
            player1.pos[0] -= 0.5 * dist * cos(rad_angle);
            player1.pos[1] -= 0.5 * dist * sin(rad_angle);

            player2.pos[0] += 0.5 * dist * cos(rad_angle);
            player2.pos[1] += 0.5 * dist * sin(rad_angle);
                    
            player1.speed = 0.5 * (player1.speed + player2.speed);
            player2.speed = player1.speed;

            //command[id] = move_command();
            //command[idx] = move_command();
        }
    }
}

void game_map::make_move() {
    double a = 1;
    
    for (size_t idx = 0; idx < players.size(); ++idx) {
        game_object& player = players[idx];
        move_command& comm = command[idx];
        
        if (comm.back) {
            double next_speed = player.speed + a;
            player.speed = next_speed < player.max_speed ? next_speed : player.max_speed;
        } else if (comm.forward) {
            double next_speed = player.speed - a;
            player.speed = -next_speed < player.max_speed ? next_speed : -player.max_speed;
        } else if (fabs(player.speed) > 1e-7) { // inertion move
            int8_t sign = player.speed > 1e-7 ? 1 : -1;
            player.speed -= sign * 0.5 * a;
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
    }
    
}
