#include "application.hpp"

application::application() :
    // window(sf::VideoMode(1920, 1080), "Bauman Racing", sf::Style::Fullscreen),
    window(sf::VideoMode(WIDTH, HEIGHT), "Bauman Racing"),
    game_context_mngr(new game_context()),
    input_mngr(new input(&window)),
    loader_mngr(new loader()),
    network_mngr(new network()),
    renderer_mngr(new renderer(&window)) {
        //window.setFramerateLimit(60);
}

bool application::run() {
   
    event e(application_run, { .empty = {} });
    loader_mngr.handle_event(e);
    event loaded = loader_mngr.throw_event();
    renderer_mngr.handle_event(loaded);

    event e_start(main_menu, { .empty = {} });
    renderer_mngr.handle_event(e_start);
//    event e_start(game_start, { .empty = {} });
//    renderer_mngr.handle_event(e_start);

    while (window.isOpen()) {
        event e_input = input_mngr.throw_event();
        switch (e_input.type) {
            case closing:
                window.close();
                break;
            case key_pressed:
                network_mngr.handle_event(e_input);
                break;
            case main_menu:
                //std::cout << "keys" << e_input.data.box.select << std::flush;
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                renderer_mngr.handle_event(e_start);
                break;
            case connect_to_open:
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                renderer_mngr.handle_event(e_start);
                break;
            case create_room:
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                renderer_mngr.handle_event(e_start);
                break;
            case connect_to_room:
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                renderer_mngr.handle_event(e_start);
                break;
            case input_ev:
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                renderer_mngr.handle_event(e_start);
                break;
            case connect_create:
                e_start.type = e_input.type;
                e_start.data = e_input.data;
                network_mngr.handle_event(e_start);
                break;
            default:
                break;
        }
//
//        event e_network = network_mngr.throw_event();
//
//        switch (e_network.type) {
//            case update_position:
//                renderer_mngr.handle_event(e_network);
//                //  + game_context
//                break;
//            default:
//                break;
//        }
    }
    return true;
}

application& application::get_instance() {
    static application instance;
    return instance;
}
