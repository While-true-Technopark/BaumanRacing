#include "application.hpp"

application::application() :
    //window(sf::VideoMode(1920, 1080), "Bauman Racing", sf::Style::Fullscreen),
    window(sf::VideoMode(1280, 720), "Bauman Racing"),
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
    
    event e_start(game_start, { .empty = {} });
    renderer_mngr.handle_event(e_start);
    
    while(window.isOpen()) {
        event e_input = input_mngr.throw_event();
        switch (e_input.type) {
            case closing:
                window.close();
                break;
            case key_pressed:
                network_mngr.handle_event(e_input);
                break;
            default:
                break;
        }
        
        event e_network = network_mngr.throw_event();
        
        switch (e_network.type) {
            case update_position:
                renderer_mngr.handle_event(e_network);
                // + game_context
                break;
            default:
                break;
        }
    }
    return true;
}

application& application::get_instance() {
    static application instance;
    return instance;
}
