#ifndef GAME_RENDER_DATA_H_
#define GAME_RENDER_DATA_H_

#include "event.hpp"
#include <vector>

struct player_data {
    player_position_info position;
    int player_id;
    int player_lap;
    int player_car_id;
    int player_race_position;
};

struct players_data {
    player_data player_1;
    player_data player_2;
    player_data player_3;
    player_data player_4;
};

struct game_render_data {
    //players_data players;
    std::vector<player_data> players;
};

#endif  // GAME_RENDER_DATA_H_
