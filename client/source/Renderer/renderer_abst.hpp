#ifndef RENDERER_ABST_H_
#define RENDERER_ABST_H_

#include <SFML/Graphics.hpp>

#include "event.hpp"
#include "game_render_data.hpp"

#define STR256 "                                                                                                                                                                                                                                                               "

class renderer_abst {
 public:
    virtual int init(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture,
        sf::Texture* logo_texture, sf::Texture* box_texture, sf::Font *main_font) = 0;
    virtual int build_game_scene(game_render_data data) = 0;
    virtual int connect_to_open(size_t box_select) = 0;
    virtual int create_room(const char (*str)[256] = &STR256) = 0;
    virtual int car_choose_menu() = 0;
    virtual int end_game_menu() = 0;
    virtual int lobby_scene() = 0;
    virtual int main_menu(size_t box_select) = 0;
    virtual int settings_menu() = 0;
    virtual int wait_scene() = 0;
 protected:
    sf::RenderWindow *window;
};

#endif  // RENDERER_ABST_H_
