#include "application.hpp"

application::application() :
    // window(sf::VideoMode(1920, 1080), "Bauman Racing", sf::Style::Fullscreen),
    window(sf::VideoMode(1000, 1000), "Bauman Racing"),
    game_context_mngr(new game_context()),
    input_mngr(new input(&window)),
    loader_mngr(new loader()),
    network_mngr(new network()),
    renderer_mngr(new renderer(&window)) {
}

bool application::run() {
    event e(application_run, { .empty = {} });
    loader_mngr.handle_event(e);
    event loaded = loader_mngr.throw_event();
    loaded.data.textures.map_number = 0;
    renderer_mngr.handle_event(loaded);
    while(window.isOpen()) {
        event e(game_start, { .empty = {} });
        renderer_mngr.handle_event(e);
    }

    return true;
}

application& application::get_instance() {
    static application instance;
    return instance;
}
