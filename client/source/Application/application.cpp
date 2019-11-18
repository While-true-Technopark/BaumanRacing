#include "application.hpp"

application::application() :
    game_context_mngr(new game_context()),
    input_mngr(new input(&window)),
    loader_mngr(new loader()),
    network_mngr(new network()),
    renderer_mngr(new renderer(&window)) {
}

bool application::run() {
    return true;
}

application& application::get_instance() {
    static application instance;
    return instance;
}
