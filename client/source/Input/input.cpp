#include "input.hpp"

int input::on_event(const event & e) {
    return 1;
}

event input::get_pressed_key() {
    event ev;
    return ev;
}

event input::throw_event() {
    event empty;
    return empty;
}

