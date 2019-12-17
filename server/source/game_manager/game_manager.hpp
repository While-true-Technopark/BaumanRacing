#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "map.hpp"

class game_manager {
 public:
    explicit game_manager(size_t num_players);
    bool load_map();
    void run();
    std::vector<game_object_type> get_setting() const;
    std::vector<position> get_players_pos() const;
    std::vector<position> get_side_objects_pos() const;
    std::vector<size_t> get_rating() const;
    bool finished(size_t id) const;
    bool finish();
    void update();
    void set_setting(size_t id, game_object_type type);
    void set_setting(size_t id, const move_command& comm);
    
 private:
    size_t num_players;
    game_map map;
    sf::Clock wait_before_start;
    bool start;
};

#endif  // GAME_MANAGER_H_
