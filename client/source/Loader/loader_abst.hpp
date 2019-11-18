#ifndef LOADER_ABST_H_
#define LOADER_ABST_H_

#include <SFML/Graphics.hpp>
#include <vector>

#include "event.hpp"


class loader_abst {
 public:
    virtual int load_all() = 0;
    virtual sf::Texture * get_texture(const std::string & name) = 0;
    // std::vector<sf::Sprite> backgrounds;
    // std::vector<sf::Sprite> cars;
    // sf::Sprite menu_button;
    // sf::Sprite left_button;
    // sf::Sprite right_button;
    // sf::Sprite round_button;
    // sf::Sprite loading;
 protected:
    bool loaded;
    std::vector<std::string> paths;
    std::vector<sf::Texture> textures;
    // std::vector<sf::Texture> backgrounds_texture;
    // std::vector<sf::Texture> cars_texture;
    // sf::Texture menu_button_texture;
    // sf::Texture left_button_texture;
    // sf::Texture right_button_texture;
    // sf::Texture round_button_texture;
    // sf::Texture loading_texture;
};

#endif  // LOADER_ABST_H_
