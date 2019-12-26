#include "application.hpp"

application::application() :
    window(sf::VideoMode(1920, 1080), "Bauman Racing"),
    // window(sf::VideoMode(1920, 1080), "Bauman Racing", sf::Style::Fullscreen),
    // window(sf::VideoMode(WIDTH, HEIGHT), "Bauman Racing"),
    game_context_mngr(new game_context()),
    input_mngr(new input(&window)),
    loader_mngr(new loader()),
    network_mngr(new network()),
    renderer_mngr(new renderer(&window)) {
        window.setFramerateLimit(60);
        event e(application_run, { .empty = {} });
        loader_mngr.handle_event(e);
}

bool application::run() {

    event loaded = loader_mngr.throw_event();
    renderer_mngr.handle_event(loaded);
    event e_start(main_menu, { .empty = {} });
    renderer_mngr.handle_event(e_start);
    //  event e_start(game_start, { .empty = {} });
    //  renderer_mngr.handle_event(e_start);

    while (window.isOpen()) {
        event e_input = input_mngr.throw_event();
        switch (e_input.type) {
            case closing:
                e_start.type = e_input.type;
                e_start.data.empty = {};
                network_mngr.handle_event(e_start);
                window.close();
                break;
            case key_pressed:
                network_mngr.handle_event(e_input);
                break;

            case main_menu:
            case connect_to_open:
            case create_room:
            case connect_to_room:
            case show_car:
            case input_ev: // TODO: обработка строки >256
                renderer_mngr.handle_event(e_input);
                break;
            case connect_create: // TODO: проверка ошибок, если такая комната уже есть
                network_mngr.handle_event(e_input);
                e_start.type = show_car;
                e_start.data.box.select = 0;
                renderer_mngr.handle_event(e_start);
                break;
            case connect_join: // TODO: проверка ошибок, если такой комнаты нет
                network_mngr.handle_event(e_input);
                e_start.type = show_car;
                e_start.data.box.select = 0;
                renderer_mngr.handle_event(e_start);
                break;
            case car_chosen:
                network_mngr.handle_event(e_input);
                e_start.type = waiting;
                e_start.data.box.select = 0;
                renderer_mngr.handle_event(e_start);
                break;
            default:
                break;
        }

        event e_network = network_mngr.throw_event();

        switch (e_network.type) {
            case update_position:
            case waiting:
                renderer_mngr.handle_event(e_network);
                break;
            case game_end:
            case game_start:
                renderer_mngr.handle_event(e_network);
                input_mngr.handle_event(e_network);
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
