#include "network_manager.hpp"

network_manager::network_manager(network_abst *abst) {
    module = abst;
}

int network_manager::handle_event(const event & e) {
    switch (e.type) {
        case key_pressed:
            module->keys_send(e.data.keys);
            break;
        case connect_create:
            module->connect(PORT, LOCAL_IP);
            network = true;
            module->create_room(&e.data.input_ev.str);
            break;
        case connect_join:
            module->connect(PORT, LOCAL_IP);
            network = true;
            module->join_room(&e.data.input_ev.str);
            break;
        case car_chosen:
            module->set_car(e.data.box.select);
            break;
        case closing:
            module->close();
            break;
        default:
            return -1;
    }
    return 0;
}

event network_manager::throw_event() {
// todo gavroman: Сделать прием координат
//    event ev;
//
//    ev.type = update_position;
//    ev.data.players_positions = module->get_positions();
    event ev(nothing_recieve, { .empty = {} });
    if (network == true) {
        json msg = module->get();
            if (msg[message::head] == message::ping && msg[message::body] == message::to) {
                module->ping();
                std::cout << "send on ping\n" << std::flush;
            } else if (msg[message::head] == message::wait) {
                ev.type = waiting;
                ev.data.box.select = msg[message::body];
                std::cout << "new " << ev.data.box.select << "\n" << std::flush;
            }  else if (msg[message::head] == message::start) {
                ev.type = game_start;
                ev.data.box.select = msg[message::body];
                std::cout << "Let's go!\n" << std::flush;
            }
    }
    
    return ev;
}
