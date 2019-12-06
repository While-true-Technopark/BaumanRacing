#include "users_room.hpp"

users_room::users_room(user&& first_clt, const std::shared_ptr<sf::SocketSelector>& selector, size_t max_users)
    : selector{selector}
    , max_users{max_users}
    , users(max_users)
    , connected(max_users, false)
    , ready(max_users, false)
    , started{false}
    , finished{false}
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

    bool all_ready = true;
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            user& clt = users[idx];
            if (selector->isReady(clt.get_socket())) {
                json msg = clt.receive();
                clt.restart_tla();
                size_t head = msg[message::head];
                switch (head) {
                    case message::setting: { // TODO: vector ready когда выбрал настройки
                        std::cout << "(room) player " << idx << " set car" << std::endl;
                        car_type type = msg[message::body];
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
        std::cout << "(room) game started" << std::endl;
        for (size_t idx = 0; idx < max_users; ++idx) {
            users[idx].send(message::start, idx);
        }
        started = true;
        manager.run();
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
                        std::cout << "╔═keys send═╗" << std::endl;
                        std::cout << "║ up    : "    << comm.forward << " ║"<< std::endl;
                        std::cout << "║ down  : "    << comm.back << " ║"<< std::endl;
                        std::cout << "║ left  : "    << comm.left_turn << " ║"<< std::endl;
                        std::cout << "║ right : "    << comm.right_turn << " ║"<< std::endl;
                        std::cout << "║ enter : "    << comm.run_sprint << " ║"<< std::endl;
                        std::cout << "║ esc   : "    << comm.throw_side_object << " ║"<< std::endl;
                        std::cout << "╚═══════════╝" << std::endl;
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

    if (manager.update()) {
        std::cout << "(room) manager update" << std::endl;
        update_user();
    }

    if (manager.finish()) {
        std::cout << "(room) game finish" << std::endl;
        finished = true;
    }
}

void users_room::update_user() const {
    for (size_t idx = 0; idx < max_users; ++idx) {
        if (connected[idx]) {
            const user& clt = users[idx];
            players_position pos;
            pos[0][0] = 1234;
            pos[0][1] = 1234;
            pos[0][2] = 1234;
            pos[1][0] = 1134;
            pos[1][1] = 1400;
            pos[1][2] = 32;
            clt.send(message::pos, pos);
            clt.send(message::rating, manager.get_rating());
            clt.send(message::pos_s, manager.get_side_objects_pos());
            // TODO:
            // if (pos update)
            // if (pos_s update) clt.send(message::pos_s, );
            // if (raiting update) send(message::rating, );
            if (manager.finished(idx)) {
                // TODO: send rating
                clt.send(message::finish, players_rating());
                //selector.remove(clt.get_socket()); // ???
                //connected[idx] = false;
                //ready[idx] = false;
            }

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
