#include <cmath>
#include "network.hpp"

network::network() {
    positions.player_1 = {
        .x = 2400.0,
        .y = 7260.0,
        .angle = 0.0,
    };
    positions.player_2 = {
        .x = 2400.0,
        .y = 7380.0,
        .angle = 0.0,
    };
    positions.player_3 = {
        .x = 2600.0,
        .y = 7260.0,
        .angle = 0.0,
    };
    positions.player_4 = {
        .x = 2600.0,
        .y = 7380.0,
        .angle = 0.0,
    };
}

event network::get_last_package() {
    event ev;
    return ev;
}

void network::keys_send(struct keys_pressed keys_input) {
    keys = keys_input;

    if (keys.up) {
        speed -= 0.5;
    }
    if (keys.down) {
        speed += 0.5;
    }
    if (keys.left) {
        positions.player_1.angle -= 4;
    }
    if (keys.right) {
        positions.player_1.angle += 4;
    }
}

void network::name_car_send(struct player_info) { }

struct players_positions_info network::get_positions() {
    positions.player_1.x += speed * cos(M_PI * positions.player_1.angle / 180);
    positions.player_1.y += speed * sin(M_PI * positions.player_1.angle / 180);
    return positions;
}

