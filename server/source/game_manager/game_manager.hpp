#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "map.hpp"
//#include "game_logic.hpp"

class game_manager {
 public:
    game_manager();
    void run();
    players_position get_players_pos() const;
    players_rating get_rating() const;
    std::vector<position> get_side_objects_pos() const;
    bool finished(size_t id) const;
    bool finish();
    void update();
    void set_setting(size_t id, car_type type);
    void set_setting(size_t id, const move_command& comm);
    
 private:
    
    game_map map;
    sf::Clock wait_before_start;
    bool start;
};

#endif  // GAME_MANAGER_H_
