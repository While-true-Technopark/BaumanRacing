#ifndef GAME_RENDER_DATA_H_
#define GAME_RENDER_DATA_H_

#include <vector>

struct player_data {
    float car_x;
    float car_y;
    float car_angle;
    int player_id;
    int player_lap;
    int player_race_position;
};

struct game_render_data {
    player_data player;
    std::vector<player_data> rivals;
};

#endif  // GAME_RENDER_DATA_H_
