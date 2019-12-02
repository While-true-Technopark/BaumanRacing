#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics.hpp>
#include "renderer_abst.hpp"
#include "event.hpp"
#include "tinyxml2.h"

class renderer : public renderer_abst {
 public:
    explicit renderer(sf::RenderWindow *win);
    // int create_cars(std::vector<sf::Texture*> cars_textures) override;
    int create_map(size_t map_number, sf::Texture* map_texture) override;
    int build_game_scene(game_render_data data) override;
    int car_choose_menu() override;
    int end_game_menu() override;
    int lobby_scene() override;
    int main_menu() override;
    int settings_menu() override;
    int wait_scene() override;

 private:
    struct map_block {
        size_t id;
        bool passable;
        sf::Sprite sprite;
        // float x;
        // float y;
        // float width;
        // float height;
    };
    std::vector<std::vector<map_block>> map;
    std::vector<std::string> paths_to_xml_maps;

    sf::Texture whole_map_texture;

    float scale;

    // std::vector<sf::Sprite*> players;
    // sf::Sprite* map_sprite;

    sf::View view;

    int parse_map();
    int build_map();
    int build_rating();
    int build_car();
    int build_cars();
};

#endif  // RENDERER_H_
