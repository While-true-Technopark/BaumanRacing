#include "user.hpp"

user::user()
    : socket{std::make_unique<sf::TcpSocket>()}
{}

json user::receive() const {
    sf::Packet packet;
    socket->receive(packet);
    return message::packet_to_json(packet);
}

bool user::ping() const {
    if (time_last_activity.getElapsedTime() > CONNECT_TIME_OUT) {
        return false;
    } 
    if (time_last_activity.getElapsedTime() > PING_TIME_OUT) {
        send(message::ping, message::to);
    }
    return true;
}

sf::TcpSocket& user::get_socket() {
    return *socket;
}

void user::restart_tla() {
    time_last_activity.restart();
}
