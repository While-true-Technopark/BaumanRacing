#ifndef USERS_ROOM_H_
#define USERS_ROOM_H_

#include <vector>
#include "user.hpp"

#define MAX_USERS 4

class users_room {
 public:
    users_room(user&& first_clt, sf::SocketSelector& selector, size_t max_users);

    /*
    не работает emplace в std::map, если оставить это
    virtual ~users_room() = default;
    users_room(const users_room&) = delete;
    users_room& operator=(const users_room&) = delete;
    users_room(users_room&&) = delete;
    users_room& operator=(users_room&&) = delete;
    */
    
    virtual void event_handler();
    bool add_user(user&& clt);
    
 private:
    sf::SocketSelector& selector;
    const size_t max_users;
    std::vector<user> users;
};

#endif  // USERS_ROOM_H_
