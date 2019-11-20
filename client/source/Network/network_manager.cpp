#include "network_manager.hpp"

network_manager::network_manager(network_abst *abst) {
    module = abst;
}

int network_manager::handle_event(const event & e) {
    switch(e.type) {
        case key_pressed:
            module->keys_send(e.data.keys);
            break;
        default:
            return -1;
    }
    return 0;
}

event network_manager::throw_event() {
    event ev(update_position, { .players_positions = module->get_positions() });
    
    return ev;
}
