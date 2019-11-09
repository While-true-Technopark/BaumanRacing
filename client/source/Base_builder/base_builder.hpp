#ifndef BASE_BUILDER_H_
#define BASE_BUILDER_H_

#include <SFML/Graphics.hpp>

class base_builder {
 private:
    sf::Sprite create_button(const std::string & text);
    sf::Text create_text(const std::string & text);
    sf::Sprite create_graphic();

    void set_position(sf::Sprite & sprite);
    void set_rotation(sf::Sprite & sprite);
};

#endif  // BASE_BUILDER_H_
