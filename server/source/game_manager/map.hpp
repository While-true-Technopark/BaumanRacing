#ifndef MAP_H_
#define MAP_H_

#include "command.hpp"

struct side_object {
    side_object();
    position pos;
    point size; // 0 - width, 1 - height
    double weight;
    sf::Clock ttl;
};

struct car {
    car();
    explicit car(car_type type);
    position pos;
    position speed;
    //point direction;
    point size; // 0 - width, 1 - height
    double weight;
    size_t num_side_objects;
    size_t num_accelerations;
    // double handleability;
    /*double max_speed;
    double max_acceleration;*/
};

class game_map {
 public:
    game_map();
    bool load_map(const std::string& path);
    
    players_position get_players_pos();
    players_rating get_rating();
    std::vector<position> get_side_objects_pos();
    
    void set_car(size_t id, car_type type);
    void set_command(size_t id, const move_command& comm);
    void make_move();
    // TODO: is update 
    //bool player_finished(size_t player_id);
    
 private:
    std::array<car, MAX_USERS> players;
    std::array<move_command, MAX_USERS> command;
    std::vector<side_object> side_objects;
    struct map_block {
        enum block_type {road = 1, wall = 2, grass = 3} type;
        point coord;
        point block_size;
    };
    std::vector<std::vector<map_block>> map_info;
    //point start_coord;
    //bool started;
    //std::array<bool, MAX_USERS> finished;
};

#endif  // MAP_H_
