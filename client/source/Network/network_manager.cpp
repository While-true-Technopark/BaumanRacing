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
            module->connect(PORT, IP);
            network = true;
            module->create_room(&e.data.input_ev.str);
            break;
        case connect_join:
            module->connect(PORT, IP);
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
    return EXIT_SUCCESS;
}

event network_manager::throw_event() {
    event ev(nothing_recieve, { .empty = {} });
    if (network) {
        json msg = module->get();
        if (msg[message::head] == message::ping && msg[message::body] == message::to) {
            module->ping();
            std::cout << "ping from server\n" << std::flush;
        } else if (msg[message::head] == message::wait) {
            ev.type = waiting;
            ev.data.box.select = msg[message::body];
            std::cout << "new " << ev.data.box.select << "\n" << std::flush;
        } else if (msg[message::head] == message::start) {
            ev.type = game_start;
            json body = msg[message::body];
            ev.data.box.select = body[message::id];
            // TODO: body[message::settings];
            std::cout << "Let's go!\n" << std::flush;
        } else if (msg[message::head] == message::pos) {
            // std::cout << "pos" << std::endl;
            ev.type = update_position;
            std::vector<position> coord = msg[message::body];
            for (size_t i = 0; i < coord.size(); ++i) {
                auto& player = ev.data.players_positions.player[i];
                position& pos = coord[i];
                player.x = pos[0];
                player.y = pos[1];
                player.angle = pos[2];
            }
        } else if (msg[message::head] == message::finish) {
            ev.type = game_end;
            ev.data.game_end.position = msg[message::body];
        }
    }
    return ev;
}
