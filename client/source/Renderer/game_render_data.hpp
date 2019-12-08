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

struct init_data {
    std::vector<sf::Texture*> cars_textures;
    sf::Texture* map_texture;
    sf::Texture* logo_texture;
    sf::Texture* box_texture;
    sf::Texture* arrow_texture;
    sf::Font *main_font;
};

#endif  // GAME_RENDER_DATA_H_
