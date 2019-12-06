#ifndef INPUT_H_
#define INPUT_H_

#include "event.hpp"
#include "input_abst.hpp"

class input : public input_abst {
 public:
    explicit input(sf::RenderWindow *win);
    struct keys_pressed_variants get_pressed_keys();
    void start_control();
    void end_control();
private:
    std::string playerInput;
};

#endif  // INPUT_H_
