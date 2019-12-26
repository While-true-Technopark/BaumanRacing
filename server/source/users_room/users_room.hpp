#ifndef USERS_ROOM_H_
#define USERS_ROOM_H_

#include "user.hpp"
#include "game_manager.hpp"
#include "logger.hpp"

class users_room final {
 public:
    users_room(user&& first_clt, const std::shared_ptr<sf::SocketSelector>& selector, size_t max_users);
    // users_room(const users_room&) = delete;
    // ~users_room();
    void event_handler();
    bool add_user(user&& clt);
    bool ping();
    size_t max_size() const;
    size_t size() const;
    std::vector<user> get_users();
    
 private:
    std::shared_ptr<sf::SocketSelector> selector;
    const size_t max_users;
    std::vector<user> users;
    std::vector<bool> connected;
    std::vector<bool> ready;
    game_manager manager;
    bool started;
    bool finished;
    void update_users();
    void before_session();
    void session();
};

#endif  // USERS_ROOM_H_
