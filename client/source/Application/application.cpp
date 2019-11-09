#include "application.hpp"

bool application::run() {
    return true;
}

int application::on_event(const event & e) {
    return 1;
}

application& application::get_instance() {
    static application instance;
    return instance;
}
