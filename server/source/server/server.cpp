#include "server.hpp"
    
// TODO: обработка исключений
// TODO: logger

server::server(size_t port, const std::string& ip) 
    : start{true}
    , selector{std::make_shared<sf::SocketSelector>()}
    
{
    if (listener.listen(port, ip) != sf::Socket::Done) {
        // throw std::runtime_error(std::strerror(errno));
    }
    selector->add(listener);
}

server::~server() {
    listener.close();
}

void server::run() {
    start = true;
    while (start) {
        if (selector->wait(UPDATE_TIME_OUT)) {
            if (selector->isReady(listener)) {
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

void server::stop() {
    start = false;
}

json server::get_info() const {
    std::map<std::string, size_t> rooms_info;
    for(auto& room: rooms) {
        rooms_info[room.first] = room.second.size();
    }
    return {{"rooms", rooms_info}, {"guests", guests.size()}};
}
    
void server::rooms_event_handler() {
    for(auto& room: rooms) {
        room.second.event_handler();
    }
}

void server::guests_event_handler() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        user& clt = guests[idx];
        if (selector->isReady(clt.get_socket())) {
            json msg = clt.receive();
            clt.restart_tla();
            size_t head = msg[message::head];
            switch (head) {
                case message::create: {
                    std::string room_name = msg[message::body][message::room_name];
                    size_t size = msg[message::body][message::size];
                    if (!rooms.count(room_name)) {
                        clt.send(message::status, message::ok);
                        rooms.emplace(room_name, users_room(std::move(clt), selector, size));
                        guests.erase(guests.begin() + idx);
                        --idx;
                        std::cout << "room " << room_name << " created" << std::endl;
                    } else {
                        clt.send(message::status, message::fail);
                        std::cout << "create failed. a room with such names exists" << std::endl;
                    }
                    break;
                }
                case message::join: {
                    std::string room_name = msg[message::body];
                    if (rooms.count(room_name) && rooms.at(room_name).size() < rooms.at(room_name).max_size()) {
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
                case message::close: {
                    std::cout << "guest " << idx << " close connection" << std::endl;
                    selector->remove(clt.get_socket());
                    guests.erase(guests.begin() + idx);
                    --idx;
                    break;
                } 
                default: {
                    clt.send(message::status, message::fail);
                    std::cout << "fail in massage" << std::endl;
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
            selector->remove(clt.get_socket());
            guests.erase(guests.begin() + idx);
            --idx;
        }
    }
}
    
void server::ping_rooms() {
    std::vector<std::string> del_rooms;
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        const std::string& room_name = it->first;
        users_room& room = it->second;
        std::cout << "ping room " << room_name << std::endl;
        if (!room.ping()) {
            std::cout << "disconnect room " << room_name << std::endl;
            del_rooms.push_back(room_name);
            std::vector<user> users = room.get_users();
            std::cout << users.size() << " members of the room became guests" << std::endl;
            //guests.emplace(guests.end(), users.begin(), users.end()); -- не работает
            for (size_t idx = 0; idx < users.size(); ++idx) {
                guests.emplace_back(std::move(users[idx]));
            }
        }
    }
    
    for (const std::string& room_name: del_rooms) {
        rooms.erase(room_name);
    }
}

bool server::add_guest() {
    user clt;
    sf::TcpSocket& socket = clt.get_socket();
    if (listener.accept(socket) == sf::Socket::Done) {
        selector->add(socket);
        guests.emplace_back(std::move(clt));
        std::cout << "add guest" << std::endl;
        return true;
    }
    return false;
}
