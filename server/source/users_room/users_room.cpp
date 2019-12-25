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
        logger::write_info("(room): map loaded");
    } else {
        logger::write_info("(room): map not loaded");
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
                        logger::write_info("(room) player " + std::to_string(idx) + " set game object type");
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
                        logger::write_info("(room) user " + std::to_string(idx) + " close connection before game");
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
            logger::write_debug("(room) wait " + std::to_string(num_users) + " users");
            clt.send(message::wait, num_users);
        }
        if (!ready[idx]) {
            all_ready = false;
        }
    }

    if (all_ready) {
        started = true;
        manager.run();
        logger::write_info("(room) game started");
        for (size_t idx = 0; idx < max_users; ++idx) {
            const user& clt = users[idx];
            clt.send(message::start, json{{message::id, idx}, {message::settings, manager.get_setting()}});
            clt.send(message::pos, manager.get_players_pos());
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
                        logger::write_trace("(room) player " + std::to_string(idx) + " set command");
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
                        logger::write_info("(room) user " + std::to_string(idx) + " close connection during the game");
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
}

void users_room::update_users() {
    if (!started) {
        return;
    }
    if (!manager.update()) {
        return;
    }
    logger::write_trace("update users");
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx] && ready[idx]) {
            const user& clt = users[idx];
            clt.send(message::pos, manager.get_players_pos());
            //clt.send(message::pos_s, manager.get_side_objects_pos());
            size_t num_finished = manager.is_finished(idx);
            if (num_finished) {
                logger::write_info("(room) player " + std::to_string(idx) + " finished " + std::to_string(num_finished));
                clt.send(message::finish, num_finished);
                ready[idx] = false;
                if (num_finished == max_users) {
                    logger::write_info("(room) game finish");
                    finished = true;
                }
            }/* else {
                clt.send(message::rating, manager.get_rating());
            }*/
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
            logger::write_info("(room) add user " + std::to_string(idx));
            return true;
        }
    }
    return false;
}

bool users_room::ping() {
    if (finished) {
        return false;
    }
    update_users();
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx] && !users[idx].ping()) {
            connected[idx] = false;
            ready[idx] = false;
            selector->remove(users[idx].get_socket());
            logger::write_info("(room) disconnect user " + std::to_string(idx));
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
    if (started) {
        for (size_t idx = 0; idx < max_users; ++idx) {
            if (connected[idx] && !ready[idx]) {
                connected[idx] = false;
                res.emplace_back(std::move(users[idx]));
            }
        }
    }
    return res;
}
