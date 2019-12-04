#ifndef USERS_ROOM_H_
#define USERS_ROOM_H_

#include "user.hpp"
#include "game_manager.hpp"

class users_room {
 public:
    users_room(user&& first_clt, sf::SocketSelector& selector, size_t max_users);

    /*
    не работает emplace в std::map, если оставить это
    virtual ~users_room() = default;
    users_room(const users_room&) = delete;
    users_room& operator=(const users_room&) = delete;
    */
    
    void event_handler();
    bool add_user(user&& clt);
    bool ping();
    
 private:
    void update_user() const;
    size_t num_connected_users() const;
    sf::SocketSelector& selector;
    const size_t max_users;
    std::vector<user> users;
    std::vector<bool> connected;
    game_manager manager;
    
 protected:
    virtual void before_session();
    virtual void session();
    bool started;
};

#endif  // USERS_ROOM_H_
