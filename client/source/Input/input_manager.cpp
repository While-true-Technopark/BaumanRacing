#include "input_manager.hpp"

input_manager::input_manager(input_abst *abst) {
    module = abst;
    current_scene = main_menu_scene;
}

int input_manager::handle_event(const event & e) {
    return 0;
}

bool input_manager::nothing_pressed(const struct keys_pressed keys) {
    return !keys.up && !keys.down && !keys.left && !keys.right && !keys.enter && !keys.esc;
}

event input_manager::throw_event() {
    event ev_input(nothing_keys, { .empty = {} });

    struct keys_pressed_variants keys = module->get_pressed_keys();

    if (keys.closing == true) {
        ev_input.type = closing;
        ev_input.data.empty = { };
    } else if (!nothing_pressed(keys.keys) && current_scene == game_scene) {
        ev_input.type = key_pressed;
        ev_input.data.keys = keys.keys;
    } else if (keys.keys.enter && current_scene == main_menu_scene && box == 0) {
        ev_input.type = connect_to_open;
        ev_input.data.empty = { };
        current_scene = connect_to_scene;
        box = 0;
    } else if (!nothing_pressed(keys.keys) && current_scene == main_menu_scene) {
        ev_input.type = main_menu;
        if (keys.keys.up && box != 0)
            box--;
        else if (keys.keys.down && box != 1)
            box++;

        ev_input.data.box.select = box;
    }  else if (keys.keys.enter && current_scene == connect_to_scene && box == 0) {
        ev_input.type = create_room;
        ev_input.data.empty = { };
        current_scene = create_room_scene;
        box = 0;
        input = "";
    }   else if (keys.keys.enter && current_scene == connect_to_scene && box == 1) {
        ev_input.type = connect_to_room;
        ev_input.data.empty = { };
        current_scene = connect_to_room_scene;
        box = 0;
        input = "";
    } else if (!nothing_pressed(keys.keys) && current_scene == connect_to_scene) {
        ev_input.type = connect_to_open;
        if (keys.keys.up && box != 0)
            box--;
        else if (keys.keys.down && box != 1)
            box++;
        
        ev_input.data.box.select = box;
    } else if (keys.keys.enter && current_scene == create_room_scene) {
        ev_input.type = connect_create;
        strcpy(ev_input.data.input_ev.str, input.c_str());
        //current_scene = create_room_scene;
        current_scene = car_choose_scene;
        input = "";
    } else if (keys.keys.enter && current_scene == connect_to_room) {
        ev_input.type = connect_join;
        strcpy(ev_input.data.input_ev.str, input.c_str());
        //current_scene = create_room_scene;
        current_scene = car_choose_scene;
        input = "";
    } else if (current_scene == connect_to_room) {
        ev_input.type = connect_to_room;
        //std::cout << input << "\n" << std::flush;
        input += keys.player_input;
        strcpy(ev_input.data.input_ev.str, input.c_str());
    } else if (current_scene == create_room_scene) {
        ev_input.type = create_room;
        //std::cout << input << "\n" << std::flush;
        input += keys.player_input;
        strcpy(ev_input.data.input_ev.str, input.c_str());
    } else if (keys.keys.enter && current_scene == car_choose_scene) {
        ev_input.type = car_chosen;
        ev_input.data.box.select = box;
        current_scene = waiting_scene;
    } else if (!nothing_pressed(keys.keys) && current_scene == car_choose_scene) {
        ev_input.type = show_car;
        if (keys.keys.left && box == 0)
            box = 2;
        else if (keys.keys.left)
            box--;
        else if (keys.keys.right)
            box = (box + 1) % 3;

        ev_input.data.box.select = box;
    }

    return ev_input;
}
