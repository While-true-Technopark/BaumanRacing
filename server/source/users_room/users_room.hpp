#ifndef USERS_ROOM_H_
#define USERS_ROOM_H_

#include "user.hpp"
#include "game_manager.hpp"

class users_room {
 public:
    users_room(user&& first_clt, const std::shared_ptr<sf::SocketSelector>& selector, size_t max_users);
    void event_handler();
    bool add_user(user&& clt);
    bool ping();
    size_t size() const;
    std::vector<user> get_users();
    
 private:
    void update_user();
    std::shared_ptr<sf::SocketSelector> selector;
    const size_t max_users;
    std::vector<user> users;
    std::vector<bool> connected;
    std::vector<bool> ready;
    game_manager manager;
    
 protected:
    virtual void before_session();
    virtual void session();
    bool started;
    bool finished;
};

#endif  // USERS_ROOM_H_
