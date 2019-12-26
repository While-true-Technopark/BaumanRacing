#ifndef RENDERER_ABST_H_
#define RENDERER_ABST_H_

#include <SFML/Graphics.hpp>

#include "event.hpp"
#include "game_render_data.hpp"

#define STR256 "                                                                                                                                                                                                                                                               "

class renderer_abst {
 public:
    virtual int build_game_scene(game_render_data data) = 0;
    virtual int build_start_scene(game_render_data data) = 0;
    virtual int car_choose_menu() = 0;
    virtual int connect_to_open(size_t box_select) = 0;
    virtual int connect_to_room(const char (*str)[256]) = 0;
    virtual int create_room(const char (*str)[256] = &STR256) = 0;
    virtual int end_game_menu(int position) = 0;
    virtual int init(init_data data) = 0;
    virtual int lobby_scene() = 0;
    virtual int main_menu(size_t box_select) = 0;
    virtual int settings_menu() = 0;
    virtual int show_car(size_t index) = 0;
    virtual int show_wait(size_t waiting) = 0;
    virtual ~renderer_abst() = default;

 protected:
    sf::RenderWindow *window;
};

#endif  // RENDERER_ABST_H_
