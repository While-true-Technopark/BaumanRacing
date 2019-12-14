#ifndef MAP_H_
#define MAP_H_

#include <SFML/Graphics/Rect.hpp>
#include "command.hpp"

struct side_object {
    side_object();
    position pos;
    double radius;
    double mass;
    sf::Clock ttl;
};

struct car {
    car();
    explicit car(car_type type);
    double dist(const position& p);
    position pos;
    double radius;
    double mass;
    size_t num_side_objects;
    size_t num_accelerations;
    double speed;
    double max_speed;
    // double handleability;
};

class game_map {
 public:
    game_map();
    bool load_map(const std::string& path);
    void set_start_pos();
    players_position get_players_pos() const;
    players_rating get_rating() const;
    std::vector<position> get_side_objects_pos() const;
    int8_t get_num_circle(size_t id) const;
    
    void set_car(size_t id, car_type type);
    void set_command(size_t id, const move_command& comm);
    void make_move();
    // TODO: is update
    //bool player_finished(size_t player_id);
    
 private:
    std::array<car, MAX_USERS> players;
    
    std::vector<side_object> side_objects;
    std::array<int8_t, MAX_USERS> num_circle;
    std::array<move_command, MAX_USERS> command;
    struct map_block {
        enum block_type {road = 1, wall = 2, grass = 3, finish = 4} type;
        sf::Rect<double> pos;
        /*point coord;
        point block_size;*/
    };
    std::vector<std::vector<map_block>> map_info;
    position start_pos;
    double start_angle;
    double road_width;
    
    void check_collision(size_t id);
    //point start_coord;
    //bool started;
    //std::array<bool, MAX_USERS> finished;
};

#endif  // MAP_H_
