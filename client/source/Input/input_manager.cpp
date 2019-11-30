#include "input_manager.hpp"

input_manager::input_manager(input_abst *abst) {
    module = abst;
}

int input_manager::handle_event(const event & e) {
    return 0;
}

bool input_manager::nothing_pressed(const struct keys_pressed keys) {
    return !keys.up && !keys.down && !keys.left && !keys.right && !keys.enter && keys.esc;
}

event input_manager::throw_event() {
    event ev_input(nothing_keys, { .empty = {} });

    struct keys_pressed_variants keys = module->get_pressed_keys();

    if (keys.closing == true) {
        ev_input.type = closing;
        ev_input.data.empty = { };
    } else if (!nothing_pressed(keys.keys)) {
        ev_input.type = key_pressed;
        ev_input.data.keys = keys.keys;
    }

    return ev_input;
}
