#ifndef INPUT_ABST_H_
#define INPUT_ABST_H_

#include <SFML/Graphics.hpp>
#include "event.hpp"

class input_abst {
 public:
    virtual struct keys_pressed get_pressed_key() = 0;
    virtual void start_control() = 0;
    virtual void end_control() = 0;
protected:
    sf::RenderWindow *window;
    bool controlling;

    struct keys_pressed keys;
};

#endif // INPUT_ABST_H_
