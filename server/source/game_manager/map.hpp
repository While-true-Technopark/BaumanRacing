#ifndef MAP_H_
#define MAP_H_

#include "command.hpp"

struct side_object {
    side_object();
    position pos;
    double radius;
    double mass;
    sf::Clock ttl;
};

struct game_object {
    game_object();
    explicit game_object(game_object_type type);
    double dist(const position& p);
    game_object_type type;
    position pos;
    double radius;
    double mass;
    size_t num_side_objects;
    size_t num_accelerations;
    double speed;
    double max_speed;
};

class game_map {
 public:
    explicit game_map(size_t num_players);
    bool load(const std::string& path);
    void start();
    std::vector<game_object_type> get_setting() const;
    std::vector<position> get_players_pos() const;
    std::vector<position> get_side_objects_pos() const;
    int get_num_circle(size_t id) const;
    void set_setting(size_t id, game_object_type type);
    void set_setting(size_t id, const move_command& comm);
    void make_move();
    
 private:
    std::vector<game_object> players;
    std::vector<int> num_circle;
    position start_pos;
    double road_width;
    std::vector<move_command> command;
    std::vector<side_object> side_objects;    
    std::vector<std::vector<bool>> blocks_type;
    double h_x;
    double h_y;    
    void check_collision(size_t id);
    void fix_num_circle();

};

#endif  // MAP_H_
