#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics.hpp>
#include "renderer_abst.hpp"
#include "event.hpp"
#include "tinyxml2.hpp"

class renderer : public renderer_abst {
 public:
    explicit renderer(sf::RenderWindow *win);
    int init(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture,
                   sf::Texture* logo_texture, sf::Texture* box_texture,
                   sf::Texture* arrow_texture, sf::Font *main_font) override;
    int build_game_scene(game_render_data data) override;
    int connect_to_open(size_t box_select) override;
    int create_room(const char (*str)[256]) override;
    int connect_to_room(const char (*str)[256]) override;
    int show_wait(size_t waiting) override;
    int show_car(size_t index) override;
    int car_choose_menu() override;
    int end_game_menu() override;
    int lobby_scene() override;
    int main_menu(size_t box_select) override;
    int settings_menu() override;
    int wait_scene() override;

 private:
    std::vector<sf::Sprite> players;
    std::vector<sf::Sprite> cars_choose;
    sf::Sprite logo;
    sf::Sprite box;
    sf::Texture map_texture;
    sf::Sprite map;
    sf::View view;
    sf::Font main_font;
    sf::Sprite arrow_l;
    sf::Sprite arrow_r;
    
    sf::Text play_text;
    sf::Text settings_text;
    sf::Text new_room_text;
    sf::Text connect_to_text;
    sf::Text connection_text;
    sf::Text enter_new_name_text;
    sf::Text enter_exists_name_text;
    sf::Text enter_name_text;
    sf::Text input_text;
    sf::Text waiting_text;

    int parse_map();
    int build_map();
    int build_rating();
    int build_car();
    int build_cars();
};

#endif  // RENDERER_H_
