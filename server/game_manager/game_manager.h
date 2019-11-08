#ifndef PROJECT_GAME_MANAGER_H_
#define PROJECT_GAME_MANAGER_H_

#include "game_logic.h"

class game_manager {
 public:
    void start_game();
    void stop_game();
    void game_builder(command comm, size_t player_id);
    std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();
 private:
    map game_map;
};

#endif  // PROJECT_GAME_MANAGER_H_
