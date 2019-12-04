#include <cmath>
#include "network.hpp"

network::network() {
    positions.player_1 = {
        .x = 2400.0,
        .y = 7260.0,
        .angle = 0.0,
    };
    positions.player_2 = {
        .x = 2400.0,
        .y = 7380.0,
        .angle = 0.0,
    };
    positions.player_3 = {
        .x = 2600.0,
        .y = 7260.0,
        .angle = 0.0,
    };
    positions.player_4 = {
        .x = 2600.0,
        .y = 7380.0,
        .angle = 0.0,
    };
}

network::~network() {
    json msg;
    
    msg = message::get_message(message::close);
    sf::Packet packet = message::json_to_packet(msg);
    socket.send(packet);
    packet.clear();
    socket.disconnect();
}

event network::get_last_package() {
    event ev;
    return ev;
}

void network::keys_send(struct keys_pressed keys_input) {
    keys = keys_input;

    if (keys.up) {
        speed -= 0.5;
    }
    if (keys.down) {
        speed += 0.5;
    }
    if (keys.left) {
        positions.player_1.angle -= 4;
    }
    if (keys.right) {
        positions.player_1.angle += 4;
    }
}

void network::name_car_send(struct player_info) { }

struct players_positions_info network::get_positions() {
    positions.player_1.x += speed * cos(M_PI * positions.player_1.angle / 180);
    positions.player_1.y += speed * sin(M_PI * positions.player_1.angle / 180);
    return positions;
}

bool network::connect(size_t port, const std::string& ip) {
    if (socket.connect(ip, port) != sf::Socket::Done) {
        // throw std::runtime_error(std::strerror(errno));
        //std::cout << "no connect" << std::flush;
        return false;
    }
    //socket.setBlocking(false);
    std::cout << "connect" << std::flush;
    return true;
}

int network::create_room(const char (*str)[256]) {
    std::cout << "create" << std::flush;
//    json msg;
//
//    std::string room_name(*str);
//    std::cin >> room_name;
//    msg = message::get_message(message::create);
//
//    msg[message::body] = room_name;

    json msg;
    
    {
        std::cout << "create a room (0), join the room (1): ";
        bool tmp = false;
        std::cin >> tmp;
        
        std::cout << "print name room: ";
        std::string room_name;
        std::cin >> room_name;
        
        if (!tmp) {
            msg = message::get_message(message::create);
        } else {
            msg = message::get_message(message::join);
        }
        
        msg[message::body] = room_name;
    }

    sf::Packet packet = message::json_to_packet(msg);
    socket.send(packet);
    packet.clear();
    
    
    while (true) {
            socket.receive(packet);
            msg = message::packet_to_json(packet);
            if (msg[message::head] == message::status) {
                break;
            }
            if (msg[message::head] == message::ping && msg[message::body] == "to") {
                msg = message::get_message(message::ping);
                msg[message::body] = "back";
                packet = message::json_to_packet(msg);
                socket.send(packet);
                std::cout << "send on ping" << std::endl;
            }
            packet.clear();
        }
    
    return 0;
}
