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
    event ev(nothing_recieve, { .empty = {} });
    if (network == true) {
        json msg = module->get();
        if (msg[message::head] == message::ping && msg[message::body] == message::to) {
            module->ping();
            std::cout << "send on ping\n" << std::flush;
            std::cout << msg[message::head] << std::flush;
        } else if (msg[message::head] == message::wait) {
            ev.type = waiting;
            ev.data.box.select = msg[message::body];
            std::cout << "new " << ev.data.box.select << "\n" << std::flush;
        } else if (msg[message::head] == message::start) {
            ev.type = game_start;
            ev.data.box.select = msg[message::body];
            std::cout << "Let's go!\n" << std::flush;
        } else if (msg[message::head] == message::pos) {
            ev.type = update_position;
            std::cout << "recieved coords" << std::flush << std::endl;
            players_position coord = msg[message::body];
            std::cout << "size : " << coord.size() << std::endl;
            std::cout << "x : " << coord[0][0] << std::flush << std::endl;
            std::cout << "y : " << coord[0][1] << std::flush << std::endl;
            std::cout << "angle : " << coord[0][2] << std::flush << std::endl;
            for (int i = 0; i != coord.size(); i++) {
                ev.data.players_positions.player[i].x = coord[i][0];
                ev.data.players_positions.player[i].y = coord[i][1];
                ev.data.players_positions.player[i].angle = coord[i][2];
            }
        }
    }

    return ev;
}
