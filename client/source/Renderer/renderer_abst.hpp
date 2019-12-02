#ifndef RENDERER_ABST_H_
#define RENDERER_ABST_H_

#include <SFML/Graphics.hpp>

#include "event.hpp"
#include "game_render_data.hpp"

class renderer_abst {
 public:
    //virtual int create_cars(std::vector<sf::Texture*> cars_textures) = 0;
    virtual int create_map(size_t map_number, sf::Texture* map_texture) = 0;
    virtual int build_game_scene(game_render_data data) = 0;
    virtual int car_choose_menu() = 0;
    virtual int end_game_menu() = 0;
    virtual int lobby_scene() = 0;
    virtual int main_menu() = 0;
    virtual int settings_menu() = 0;
    virtual int wait_scene() = 0;
    std::vector<sf::Sprite*> players;
    sf::Sprite map_sprite;
 protected:
    sf::RenderWindow *window;
};

#endif  // RENDERER_ABST_H_
