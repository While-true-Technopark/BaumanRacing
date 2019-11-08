#ifndef BAUMANRACING_CONNECTION_H
#define BAUMANRACING_CONNECTION_H

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "../game_logic/map.h"

class connection {
public:
    command get_player_event();
    unsigned get_id();
    sf::TcpSocket* get_socket();
    void set_timeout(sf::Time time);
    void update(float delta);
private:
    player player;
    unsigned room_id;
    sf::Time timeout;
    std::unique_ptr<sf::TcpSocket> server_access;
};


#endif //BAUMANRACING_CONNECTION_H
