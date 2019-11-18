#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics.hpp>
#include "renderer_abst.hpp"
#include "event.hpp"

class renderer : public renderer_abst {
 public:
    renderer(sf::RenderWindow *win);
    int build_game_scene(game_render_data data) override;
    int car_choose_menu() override;
    int end_game_menu() override;
    int lobby_scene() override;
    int main_menu() override;
    int settings_menu() override;
    int wait_scene() override;
 private:
    int build_map();
    int build_rating();
    int build_car();
    int build_cars();
};

#endif  // RENDERER_H_
