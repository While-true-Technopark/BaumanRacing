#include "users_room.hpp"

users_room::users_room(user&& first_clt, sf::SocketSelector& selector, size_t max_users)
    : selector{selector}
    , max_users{max_users}
{
    users.emplace_back(std::move(first_clt));
}

void users_room::event_handler() {
    for (size_t idx = 0; idx < users.size(); ++idx) {
        user& clt = users[idx];
        if (selector.isReady(*(clt.socket))) {}
    }
}

bool users_room::add_user(user&& clt) {
    if (users.size() < max_users) {
        users.emplace_back(std::move(clt));
        return true;
    }
    return false;
}
