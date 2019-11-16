#include "network_manager.hpp"

network_manager::network_manager(network_abst *abst) {
    
}

int network_manager::on_event(const event & e) {
    return 0;
}

event network_manager::throw_event() {
    event ev;
    return ev;
}
