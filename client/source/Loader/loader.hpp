#ifndef LOADER_H_
#define LOADER_H_

#include "base_module.hpp"
#include "event.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class loader : public base_module {
 public:
    int on_event(const event & e);
    std::vector<sf::Sprite> backgrounds;
    std::vector<sf::Sprite> cars;
    sf::Sprite menu_button;
    sf::Sprite left_button;
    sf::Sprite right_button;
    sf::Sprite round_button;
    sf::Sprite loading;
 private:
    int load_all();
    std::vector<std::string> paths;
    std::vector<sf::Texture> backgrounds_texture;
    std::vector<sf::Texture> cars_texture;
    sf::Texture menu_button_texture;
    sf::Texture left_button_texture;
    sf::Texture right_button_texture;
    sf::Texture round_button_texture;
    sf::Texture loading_texture;
};

#endif  // LOADER_H_
