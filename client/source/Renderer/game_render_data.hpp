#ifndef GAME_RENDER_DATA_H_
#define GAME_RENDER_DATA_H_

#include "event.hpp"
#include <vector>

struct player_data {
    player_position_info position;
    int id;
    int lap;
    int car_id;
    int race_position;
};

struct game_render_data {
    std::array<player_data, MAX_USERS> players;
};

#endif  // GAME_RENDER_DATA_H_
