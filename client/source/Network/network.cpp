#include "network.hpp"

int network::on_event(const event & e) {
    return 1;
}

event network::get_last_package() {
    event ev;
    return ev;
}

event network::throw_event() {
    event empty;
    return empty;
}
