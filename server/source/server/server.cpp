#include "server.hpp"
    
// TODO: обработка исключений
// TODO: написать обработчики событий
// TODO: logger

server::server(size_t port, const std::string& ip) {
    if (listener.listen(port, ip) != sf::Socket::Done) {
        // throw std::runtime_error(std::strerror(errno));
    }
    selector.add(listener);
    std::cout << "server is started and waiting for clients" << std::endl;
}

server::~server() {
    listener.close();
}

void server::run() {
    while (true) {
        if (selector.wait(PING_TIME_OUT)) {
            if (selector.isReady(listener)) {
                add_guest();
            } else {
                rooms_event_handler();
                guests_event_handler();
            }
        }
        ping_rooms();
        ping_guests();
    }
}
    
void server::rooms_event_handler() {
    for(auto& room : rooms) {
        room.second.event_handler();
    }
}
    
void server::guests_event_handler() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        user& clt = guests[idx];
        if (selector.isReady(*(clt.socket))) {
            sf::Packet packet;
            clt.socket->receive(packet);
            clt.restart_time_last_activity();
            json msg = message::packet_to_json(packet);
            auto head = msg[message::head];
            if (head == message::create) {
                clt.send(message::status, message::ok);
                // TODO: обработка, если комната с таким именем уже существует
                std::string room_name = msg[message::body];
                rooms.emplace(room_name, users_room(std::move(clt), selector, MAX_USERS));
                std::cout << "room " << room_name << " created" << std::endl;
            } else if (head == message::join) {
                clt.send(message::status, message::ok);
                std::string room_name = msg[message::body];
                // TODO: обработка, если комнаты с таким именем не существует
                rooms.at(room_name).add_user(std::move(clt));
                std::cout << "client joined in room " << room_name << std::endl;
            } else if (head == message::ping) {
                if (msg[message::body] == message::to) {
                    clt.send(message::ping, message::back);
                }
            } else {
                clt.send(message::ping, message::fail);
                selector.remove(*(clt.socket));
                std::cout << "fail in massage" << std::endl;
            }
            guests.erase(guests.begin() + idx);
            --idx;
        }
    }
}
    
void server::ping_guests() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        std::cout << "ping guest " << idx << std::endl;
        user& clt = guests[idx];
        if (!clt.ping()) {
            std::cout << "disconnect guest " << idx << std::endl;
            selector.remove(*(clt.socket));
            guests.erase(guests.begin() + idx);
            --idx;
        }
    }
}
    
void server::ping_rooms() {
    std::cout << "ping rooms" << std::endl;
}

bool server::add_guest() {
    user clt;
    if (listener.accept(*(clt.socket)) == sf::Socket::Done) {
        selector.add(*(clt.socket));
        guests.emplace_back(std::move(clt));
        std::cout << "add guest" << std::endl;
        return true;
    }
    return false;
}
