#ifndef INPUT_H_
#define INPUT_H_

#include "event.hpp"
#include "base_module.hpp"
#include "event_throwable.hpp"

class input : public base_module, event_throwable {
 public:
    int on_event(const event & e);
    event get_pressed_key();
    event throw_event();
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
