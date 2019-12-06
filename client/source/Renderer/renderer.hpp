#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics.hpp>
#include "renderer_abst.hpp"
#include "event.hpp"

class renderer : public renderer_abst {
 public:
    explicit renderer(sf::RenderWindow *win);
    int init(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture,
                   sf::Texture* logo_texture, sf::Texture* box_texture,
                   sf::Texture* arrow_texture, sf::Font *main_font) override;
    int build_game_scene(game_render_data data) override;
    int car_choose_menu() override;
    int connect_to_open(size_t box_select) override;
    int connect_to_room(const char (*str)[256]) override;
    int create_room(const char (*str)[256]) override;
    int end_game_menu() override;
    int lobby_scene() override;
    int main_menu(size_t box_select) override;
    int settings_menu() override;
    int show_car(size_t index) override;
    int show_wait(size_t waiting) override;
    int wait_scene() override;
    ~renderer() override;

 private:
    sf::Vector2u window_size;

    // sf::Font main_font;
    struct sprite_props {
        sf::Texture* texture;
        bool centered;
        sf::Vector2f position;
        float rotation;
        sf::Vector2f scale;
    };
    sf::Sprite arrow_l;
    sf::Sprite arrow_r;
    sf::Sprite box;
    sf::Sprite logo;
    sf::Sprite map;
    // sf::Texture map_texture;
    sf::View view;
    std::vector<sf::Sprite> cars_choose;
    std::vector<sf::Sprite> players;

    struct text_props {
        sf::Color fill_color;
        sf::Font* font;
        bool centered; // "top-left", "center"
        sf::Vector2f position;
        std::string string;
    };
    sf::Text connect_to_text;
    sf::Text connection_text;
    sf::Text enter_exists_name_text;
    sf::Text enter_name_text;
    sf::Text enter_new_name_text;
    sf::Text input_text;
    sf::Text new_room_text;
    sf::Text play_text;
    sf::Text settings_text;
    sf::Text waiting_text;

    sf::Text build_text(const text_props props);
    sf::Sprite build_sprite(const sprite_props props);
    int build_car();
    int build_cars();
    int build_map();
    int build_rating();
};

#endif  // RENDERER_H_
