#include "map.hpp"
#include "tinyxml2.hpp"

static double GRAD_CIRCLE = 360; // в градусах
static float FLOAT_ZERO = 1e-4;
static double DOUBLE_ZERO = 1e-7;

side_object::side_object() 
    : radius{15}
    , mass{1}
{
    pos.fill(0);
}

game_object::game_object()
    : game_object(game_object_type::medium)
{}

game_object::game_object(game_object_type type) 
    : type{type}
    , speed{0}
{
    pos.fill(0);
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
{}

bool game_map::load(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        return false;
    }
    
    tinyxml2::XMLElement* map_xml = doc.FirstChildElement("map");
    if (!map_xml) {
        return false;
    }
    size_t num_block_x = map_xml->IntAttribute("width", 0);
    size_t num_block_y = map_xml->IntAttribute("height", 0);
    h_x = map_xml->IntAttribute("tilewidth", 0);
    h_y = map_xml->IntAttribute("tileheight", 0);
    
    start_pos = {3830, 7320, 0}; // TODO: из файла (Рома)
    road_width = 440;

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    for (size_t j = 0; j < num_block_y; ++j) {
        std::vector<bool> row(num_block_x);
        for (size_t i = 0; i <  num_block_x; ++i) {
            size_t block_type = tile_xml->IntAttribute("gid", 1);
            row[i] = (block_type == 1 || block_type == 4) ? true : false; // road - 1, finish - 4
            tile_xml = tile_xml->NextSiblingElement("tile");
        }
        blocks_type.emplace_back(std::move(row));
    }
    return true;
}

void game_map::start() {
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

std::vector<game_object_type> game_map::get_setting() const {
    std::vector<game_object_type> setting(players.size());
    for (size_t idx = 0; idx < setting.size(); ++idx) {
        setting[idx] = players[idx].type;
    }
    return setting;
}

std::vector<position> game_map::get_players_pos() const {
    std::vector<position> pos(players.size());
    for (size_t idx = 0; idx < pos.size(); ++idx) {
        pos[idx] = players[idx].pos;
    }
    return pos;
}

std::vector<position> game_map::get_side_objects_pos() const {
    std::vector<position> pos(side_objects.size());
    for (size_t idx = 0; idx < side_objects.size(); ++idx) {
        pos[idx] = side_objects[idx].pos;
    }
    return pos;
}

int game_map::get_num_circle(size_t id) const {
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
    
    size_t i = player1.pos[0] / h_x;
    size_t j = player1.pos[1] / h_y;
    if (!(j < blocks_type.size()) || !(i < blocks_type[j].size()) || !blocks_type[j][i]) {
        player1.pos[0] -= 0.5 * player1.speed * cos(rad_angle);
        player1.pos[1] -= 0.5 * player1.speed * sin(rad_angle);
        player1.speed = 0;
    }
            
    for (size_t idx = 0; idx < players.size(); ++idx) {
        if (idx == id) {
            continue;
        }
        game_object& player2 = players[idx];
        double dist = player1.dist(player2.pos) - (player1.radius + player2.radius);
        if (dist < FLOAT_ZERO) {
            player1.pos[0] -= 0.5 * dist * cos(rad_angle);
            player1.pos[1] -= 0.5 * dist * sin(rad_angle);

            player2.pos[0] += 0.5 * dist * cos(rad_angle);
            player2.pos[1] += 0.5 * dist * sin(rad_angle);
                    
            player1.speed = 0.5 * (player1.speed + player2.speed);
            player2.speed = player1.speed;
        }
    }
}

void game_map::fix_num_circle() {
    double x_beg = start_pos[0] - 30;
    double x_end = start_pos[0] + 30;
    double y_down = start_pos[1] - road_width;
    double y_up = start_pos[1] + road_width;
    
    for (size_t idx = 0; idx < players.size(); ++idx) {
        game_object& player = players[idx];
        if (player.pos[0] > x_beg && player.pos[0] < x_end && player.pos[1] > y_down && player.pos[1] < y_up) {
            double next_x = player.pos[0] + player.speed * cos(player.pos[2] * 2. * M_PI / GRAD_CIRCLE);
            if (next_x < x_beg) {
                ++num_circle[idx];
            } else if (next_x > x_end) {
                --num_circle[idx];
            }
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
        } else if (fabs(player.speed) > DOUBLE_ZERO) { // inertion move
            int8_t sign = player.speed > DOUBLE_ZERO ? 1 : -1;
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
    fix_num_circle();
}
