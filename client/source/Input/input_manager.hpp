#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "input_abst.hpp"
#include "event_throwable.hpp"

class input_manager : public base_manager, event_throwable {
 public:
    explicit input_manager(input_abst *abst);
    int handle_event(const event & e);
    bool nothing_pressed(const struct keys_pressed *keys);
    bool changed(const struct keys_pressed *keys, const struct keys_pressed *keys_old);
    event throw_event();
    input_abst *module;
private:
    enum scene_types {
        main_menu_scene,
        settings_scene,
        connect_to_scene,
        create_room_scene,
        connect_to_room_scene,
        car_choose_scene,
        lobby_scene,
        waiting_scene,
        game_scene,
        end_game_scene,
        users_scene,
        bad_name_scene
    };
    
    scene_types current_scene;
    size_t box;
    std::string input;
    struct keys_pressed keys_old = { };
};

#endif  // INPUT_MANAGER_H_
