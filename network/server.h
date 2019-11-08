#ifndef BAUMANRACING_SERVER_H
#define BAUMANRACING_SERVER_H

#include <SFML/Network.hpp>

class server {
public:
    void run();
private:
    unsigned port;
    sf::SocketSelector socket_manager;
    sf::TcpListener listener;
    sf::IpAddress ip_address;
};


#endif //BAUMANRACING_SERVER_H

