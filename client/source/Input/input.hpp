#ifndef INPUT_H_
#define INPUT_H_

#include "event.hpp"
#include "input_abst.hpp"

class input : public input_abst {
 public:
    input(sf::RenderWindow *win);
    struct keys_pressed get_pressed_key();
    void start_control();
    void end_control();
 private:
    enum scene_types {
        main_menu,
        settings,
        car_choose,
        lobby,
        waiting,
        game,
        end_game
    };
    
    scene_types current_scene;
    
    
};

#endif // INPUT_H_
