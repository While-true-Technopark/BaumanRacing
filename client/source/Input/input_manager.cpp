#include "input_manager.hpp"

input_manager::input_manager(input_abst *abst) {

}

int input_manager::handle_event(const event & e) {
    return 0;
}

event input_manager::throw_event() {
    event ev;
    return ev;
}
