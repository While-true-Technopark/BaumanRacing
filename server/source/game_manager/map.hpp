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

struct game_object {
    game_object();
    explicit game_object(game_object_type type);
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
    explicit game_map(size_t num_players);
    bool load_map(const std::string& path);
    void set_start_pos();
    players_position get_players_pos() const;
    players_rating get_rating() const;
    std::vector<position> get_side_objects_pos() const;
    int8_t get_num_circle(size_t id) const;
    
    void set_setting(size_t id, game_object_type type);
    void set_setting(size_t id, const move_command& comm);
    void make_move();
    // TODO: is update
    //bool player_finished(size_t player_id);
    
 private:
    std::vector<game_object> players;
    std::vector<int8_t> num_circle;
    std::vector<move_command> command;
    std::vector<side_object> side_objects;

    double h_x;
    double h_y;
    struct map_block {
        enum block_type {road = 1, wall = 2, grass = 3, finish = 4} type;
        sf::Rect<double> pos;
        /*point coord;
        point block_size;*/
    };
    std::vector<std::vector<map_block>> map_info;
    position start_pos;
    double road_width;
    
    void check_collision(size_t id);
    //point start_coord;
    //bool started;
    //std::array<bool, MAX_USERS> finished;
};

#endif  // MAP_H_
