#include "server.hpp"

server::server(size_t port, const std::string& ip) noexcept
    : start{true}
    , selector{std::make_shared<sf::SocketSelector>()}

{
    listener.listen(port, ip);
    selector->add(listener);
    logger::init_logger("server.log");
    logger::write_info("(server): init");
}

server::~server() {
    listener.close();
}

void server::run() {
    logger::write_info("(server): run");
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
    logger::write_info("(server): stop");
    start = false;
}

json server::get_info() const {
    std::unordered_map<std::string, size_t> rooms_info;
    for(const auto& [room_name, room]: rooms) {
        rooms_info[room_name] = room.size();
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
                    json body = msg[message::body];
                    std::string room_name = body[message::room_name];
                    size_t room_size = body[message::size];
                    if (room_size && !rooms.count(room_name)) {
                        clt.send(message::status, message::ok);
                        rooms.emplace(room_name, users_room(std::move(clt), selector, room_size));
                        guests.erase(guests.begin() + idx);
                        --idx;
                        logger::write_info("(server): room " + room_name + " created");
                    } else {
                        clt.send(message::status, message::fail);
                        logger::write_info("(server): create failed. a room with such names exists");
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
                        logger::write_info("(server): client joined in room " + room_name);
                    } else {
                        logger::write_info("(server): join failed. no room with that name exists or is already full");
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
                    logger::write_info("(server): guest " + std::to_string(idx) + " close connection");
                    selector->remove(clt.get_socket());
                    guests.erase(guests.begin() + idx);
                    --idx;
                    break;
                }
                default: {
                    clt.send(message::status, message::fail);
                    logger::write_info("(server): fail in massage");
                }
            }
        }
    }
}

void server::ping_guests() {
    for (size_t idx = 0; idx < guests.size(); ++idx) {
        user& clt = guests[idx];
        if (!clt.ping()) {
            logger::write_info("(server): disconnect guest " + std::to_string(idx));
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
        if (!room.ping()) {
            del_rooms.push_back(room_name);
            std::vector<user> users = room.get_users();
            logger::write_info("(server): disconnect room " + room_name);
        }
        std::vector<user> users = room.get_users();
        if (!users.empty()) {
            logger::write_info("(server): " + std::to_string(users.size()) + " user(s) leave the room " + room_name);
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
        logger::write_info("(server): add guest");
        return true;
    }
    return false;
}
