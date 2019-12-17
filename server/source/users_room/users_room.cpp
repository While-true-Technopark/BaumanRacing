#include "users_room.hpp"

users_room::users_room(user&& first_clt, const std::shared_ptr<sf::SocketSelector>& selector, size_t max_users)
    : selector{selector}
    , max_users{max_users}
    , users(max_users)
    , connected(max_users, false)
    , ready(max_users, false)
    , manager(max_users)
    , started{false}
    , finished{false}
{
    if (manager.load_map()) {
        // log
    } else {
        // log
    }
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

    bool all_ready = true;
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            user& clt = users[idx];
            if (selector->isReady(clt.get_socket())) {
                json msg = clt.receive();
                clt.restart_tla();
                size_t head = msg[message::head];
                switch (head) {
                    case message::setting: {
                        std::cout << "(room) player " << idx << " set car" << std::endl;
                        game_object_type type = msg[message::body];
                        manager.set_setting(idx, type);
                        ready[idx] = true;
                        break;
                    }
                    case message::ping: {
                        if (msg[message::body] == message::to) {
                            clt.send(message::ping, message::back);
                        }
                        break;
                    }
                    case message::close: {
                        std::cout << "(room) user " << idx << " close connection before game" << std::endl;
                        connected[idx] = false;
                        ready[idx] = false;
                        selector->remove(clt.get_socket());
                        break;
                    }
                    default: {
                        clt.send(message::status, message::fail);
                    }
                }
            }

            size_t num_users = size();
            std::cout << "(room) wait " << num_users << " users" << std::endl;
            clt.send(message::wait, num_users);
        }
        if (!ready[idx]) {
            all_ready = false;
        }
    }

    if (all_ready) {
        started = true;
        manager.run();
        std::cout << "(room) game started" << std::endl;
        for (size_t idx = 0; idx < max_users; ++idx) {
            const user& clt = users[idx];
            clt.send(message::start, json{{message::id, idx}, {message::settings, manager.get_setting()}});
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
            if (selector->isReady(clt.get_socket())) {
                json msg = clt.receive();
                clt.restart_tla();
                size_t head = msg[message::head];
                switch (head) {
                    case message::command: {
                        std::cout << "(room) player " << idx << " set command" << std::endl;
                        move_command comm(msg[message::body]);
                        manager.set_setting(idx, comm);
                        break;
                    }
                    case message::ping: {
                        if (msg[message::body] == message::to) {
                            clt.send(message::ping, message::back);
                        }
                        break;
                    }
                    case message::close: {
                        std::cout << "(room) user " << idx << " close connection during the game" << std::endl;
                        connected[idx] = false;
                        ready[idx] = false;
                        selector->remove(clt.get_socket());
                        break;
                    }
                    default: {
                        clt.send(message::status, message::fail);
                    }
                }
            }
        }
    }

    // update_user();
}

void users_room::update_user() {
    if (!started) {
        return;
    }
    std::cout << "(room) manager update" << std::endl;
    manager.update();
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            const user& clt = users[idx];
            clt.send(message::pos, manager.get_players_pos());
            clt.send(message::pos_s, manager.get_side_objects_pos());
            if (manager.finished(idx)) {
                clt.send(message::finish, manager.get_rating());
            } else {
                clt.send(message::rating, manager.get_rating());
            }

        }
    }
    
    if (manager.finish()) {
        std::cout << "(room) game finish" << std::endl;
        finished = true;
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
            std::cout << "(room) add user " << idx << std::endl;
            return true;
        }
    }
    return false;
}

bool users_room::ping() {
    if (finished) {
        return false;
    }
    update_user();
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx] && !users[idx].ping()) {
            connected[idx] = false;
            ready[idx] = false;
            selector->remove(users[idx].get_socket());
            std::cout << "(room) disconnect user " << idx << std::endl;
        }
    }
    return size();
}

size_t users_room::max_size() const {
    return max_users;
}

size_t users_room::size() const {
    size_t res = 0;
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            ++res;
        }
    }
    return started && res ? max_users : res;
}

std::vector<user> users_room::get_users() {
    std::vector<user> res;
    if (finished) {
        for (size_t idx = 0; idx < max_users; ++idx) {
            if (connected[idx]) {
                connected[idx] = false;
                ready[idx] = false;
                res.emplace_back(std::move(users[idx]));
            }
        }
    }
    return res;
}
