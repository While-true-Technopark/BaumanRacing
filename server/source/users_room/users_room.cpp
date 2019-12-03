#include "users_room.hpp"

users_room::users_room(user&& first_clt, sf::SocketSelector& selector, size_t max_users)
    : selector{selector}
    , max_users{max_users}
    , users(max_users)
    , connected(max_users, false)
    , started{false}
{
    users[0] = std::move(first_clt);
    connected[0] = true;
}

void users_room::event_handler() {
    if (!started) {
        return before_session();
    }
    return session();
}

void users_room::before_session() {
    if (started) {
        return;
    }
    
    size_t num_users = num_connected_users();
    if (num_users == max_users) {
        started = true;
    }
    
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            user& clt = users[idx];
            if (selector.isReady(clt.get_socket())) {
                json msg = clt.receive();
                clt.restart_tla();
                size_t head = msg[message::head];
                switch (head) {
                    case message::setting: {
                        // TODO:
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
                        break;
                    }
                }
            }
        
            if (!started) {
                clt.send(message::wait, num_users);
            } else {
                clt.send(message::start, idx);
            }
            
        }
    }
}

void users_room::session() {
    if (!started) {
        return;
    }
    
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            user& clt = users[idx];
            if (selector.isReady(clt.get_socket())) {
                json msg = clt.receive();
                clt.restart_tla();
                size_t head = msg[message::head];
                switch (head) {
                    case message::command: {
                        // TODO:
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
                        break;
                    }
                }
            }
            // TODO:
            // if (coord update) clt.send(message::coord, );
            // if (coord_s update) clt.send(message::coord_s, );
            // if (raiting update) send(message::rating, );
            
        }
    }
}

bool users_room::add_user(user&& clt) {
    if (started) {
        return false;
    }
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (!connected[idx]) {
            users[idx] = std::move(clt);
            connected[idx] = true;
            return true;
        }
    }
    return false;
}

bool users_room::ping() {
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx] && !users[idx].ping()) {
            connected[idx] = false;
            selector.remove(users[idx].get_socket());
        }
    }
    return num_connected_users();
}

size_t users_room::num_connected_users() const {
    size_t res = 0;
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            ++res;
        }
    }
    return res;
}
