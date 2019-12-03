#ifndef MAP_H_
#define MAP_H_

#include "def.hpp"

struct side_object {
    point coord;
    point size; // 0 - width, 1 - height
    double weight;
    size_t ttl; // time
};

struct car {
    point coord;
    point size; // 0 - width, 1 - height
    double weight;
    point speed;
    point direction;
    size_t num_side_objects;
    // double handleability;
    /*double max_speed;
    double max_acceleration;*/
};

class game_map {
 public:
    /*explicit*/ map(/*size_t map_id*/);
    players_coord get_players_coord();
    players_rating get_rating();
    std::vector<point> get_side_objects_coord();
    
    void set_car(size_t player_id, car_type type) {}
    void set_command(size_t player_id, const command& comm) {}
    void make_move() {}
    
    // TODO: is update 
    //bool player_finished(size_t player_id);
    
 private:
    std::array<car, MAX_USERS> players;
    std::vector<side_object> side_objects;
    struct map_block {
        enum {road = 1, wall = 2, grass = 3} type_block;
        point coord;
        point block_size;
    };
    std::vector<std::vector<map_block>> map_info;
};

#endif  // MAP_H_
