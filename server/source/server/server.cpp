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
    for(auto& room: rooms) {
        room.second.event_handler();
    }
}
    
void server::guests_event_handler() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        user& clt = guests[idx];
        if (selector.isReady(clt.get_socket())) {
            json msg = clt.receive();
            clt.restart_tla();
            // TODO: в случае, когда срабатывает деструктор клиента он сюда чет шлет и json при паринге тут падает так как у него нет заголовка
            size_t head = msg[message::head];
            switch (head) {
                case message::create: {
                    std::string room_name = msg[message::body];
                    if (!rooms.count(room_name)) {
                        clt.send(message::status, message::ok);
                        rooms.emplace(room_name, users_room(std::move(clt), selector, MAX_USERS));
                        guests.erase(guests.begin() + idx);
                        --idx;
                        std::cout << "room " << room_name << " created" << std::endl;
                    } else {
                        clt.send(message::status, message::fail);
                        std::cout << "create failed. a room with such names exists" << std::endl;;
                    }
                    break;
                }
                case message::join: {
                    std::string room_name = msg[message::body];
                    // TODO: обработка, если комната уже заполнена
                    if (rooms.count(room_name)) {
                        clt.send(message::status, message::ok);
                        rooms.at(room_name).add_user(std::move(clt));
                        guests.erase(guests.begin() + idx);
                        --idx;
                        std::cout << "client joined in room " << room_name << std::endl;
                    } else {
                        std::cout << "join failed. no room with that name exists or is already full" << std::endl;;
                        clt.send(message::status, message::fail);
                    }
                    break;
                }
                case message::ping: {
                    if (msg[message::body] == message::to) {
                        clt.send(message::ping, message::back);
                    }
                    break;
                } 
                default: {
                    clt.send(message::status, message::fail);
                    std::cout << "fail in massage" << std::endl;
                    break;
                }
            }
        }
    }
}
    
void server::ping_guests() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        std::cout << "ping guest " << idx << std::endl;
        user& clt = guests[idx];
        if (!clt.ping()) {
            std::cout << "disconnect guest " << idx << std::endl;
            selector.remove(clt.get_socket());
            guests.erase(guests.begin() + idx);
            --idx;
        }
    }
}
    
void server::ping_rooms() {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        std::cout << "ping room " << it->first << std::endl;
        if (!it->second.ping()) {
            // TODO: удаление комнаты
        }
    }
}

bool server::add_guest() {
    user clt;
    sf::TcpSocket& socket = clt.get_socket();
    if (listener.accept(socket) == sf::Socket::Done) {
        selector.add(socket);
        guests.emplace_back(std::move(clt));
        std::cout << "add guest" << std::endl;
        return true;
    }
    return false;
}
