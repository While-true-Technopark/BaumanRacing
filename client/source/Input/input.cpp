#include "input.hpp"

input::input(sf::RenderWindow *win) {
    window = win;
    current_scene = game;
}

struct keys_pressed_variants input::get_pressed_keys() {
    struct keys_pressed_variants keys = { };
    
    sf::Event event = sf::Event();
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                keys.closing = true;
                break;
            }
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        keys.keys.up = true;
                        break;
                    case sf::Keyboard::Down:
                        keys.keys.down = true;
                        break;
                    case sf::Keyboard::Left:
                        keys.keys.left = true;
                        break;
                    case sf::Keyboard::Right:
                        keys.keys.right = true;
                        break;
                    case sf::Keyboard::Enter:
                        keys.keys.enter = true;
                        break;
                    case sf::Keyboard::Escape:
                        keys.keys.esc = true;
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased: {
                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        keys.keys.up = false;
                        break;
                    case sf::Keyboard::Down:
                        keys.keys.down = false;
                        break;
                    case sf::Keyboard::Left:
                        keys.keys.left = false;
                        break;
                    case sf::Keyboard::Right:
                        keys.keys.right = false;
                        break;
                    case sf::Keyboard::Enter:
                        keys.keys.enter = false;
                        break;
                    case sf::Keyboard::Escape:
                        keys.keys.esc = false;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
    
    return keys;
}

void input::start_control() {

}

void input::end_control() {

}
