#include <cmath>
#include "network.hpp"

network::network() {
}

network::~network() {
}

template<class type>
void network::send(message::header head, const type& body) {
    json msg = message::get_message(head);
    msg[message::body] = body;
    sf::Packet packet = message::json_to_packet(msg);
    socket.send(packet);
}

json network::get() { // receive
    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done) {
        return json();
    } else {
        return message::packet_to_json(packet);
    }
}

event network::get_last_package() {
    event ev;
    return ev;
}


void network::ping() {
    send(message::ping, message::back);
}


void network::keys_send(struct keys_pressed keys_input) {
//    std::cout << "╔═keys send═╗" << std::endl;
//    std::cout << "║ up    : "    << keys_input.up    << " ║"<< std::endl;
//    std::cout << "║ down  : "    << keys_input.down  << " ║"<< std::endl;
//    std::cout << "║ left  : "    << keys_input.left  << " ║"<< std::endl;
//    std::cout << "║ right : "    << keys_input.right << " ║"<< std::endl;
//    std::cout << "║ enter : "    << keys_input.enter << " ║"<< std::endl;
//    std::cout << "║ esc   : "    << keys_input.esc   << " ║"<< std::endl;
//    std::cout << "╚═══════════╝" << std::endl;

    move_command keys_to_send;
    keys_to_send.forward = keys_input.up;
    keys_to_send.back = keys_input.down;
    keys_to_send.right_turn = keys_input.right;
    keys_to_send.left_turn = keys_input.left;
    keys_to_send.run_sprint = keys_input.enter;
    keys_to_send.throw_side_object = keys_input.esc;

    send(message::command, keys_to_send.get_json());
}

void network::name_car_send(struct player_info) { }

struct players_positions_info network::get_positions() {
    return positions;
}

bool network::connect(size_t port, const std::string& ip) {
    if (socket.connect(ip, port) != sf::Socket::Done) {
        std::cout << "no connect\n" << std::flush;
        return false;
    }
    socket.setBlocking(false);
    std::cout << "connect\n" << std::flush;
    return true;
}

int network::create_room(const char (*str)[256]) {
    std::cout << "create\n" << std::flush;
    std::string room_name(*str);
    send(message::create, json{{message::room_name, room_name}, {message::size, MAX_USERS}}); // TODO: (Слава) удалить MAX_USERS из конфига 
    return EXIT_SUCCESS;
}

int network::set_car(size_t index) {
    std::cout << "set car\n" << std::flush;
    send(message::setting, static_cast<game_object_type>(index));
    return EXIT_SUCCESS;
}

int network::join_room(const char (*str)[256]) {
    std::cout << "join\n" << std::flush;
    std::string room_name(*str);
    send(message::join, room_name);
    return EXIT_SUCCESS;
}

int network::close() {
    std::cout << "delete it\n" << std::flush;
    send(message::close, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
