#include "user.hpp"

user::user()
    : socket{std::make_unique<sf::TcpSocket>()}
{}

void user::send(message::header _header, const std::string body) {
    json msg = message::get_message(_header);
    msg[message::body] = body;
    sf::Packet packet = message::json_to_packet(msg);
    socket->send(packet);
}

json user::receive() {
    sf::Packet packet;
    socket->receive(packet);
    return message::packet_to_json(packet);
}

sf::TcpSocket& user::get_socket() {
    return *socket;
}

bool user::ping() {
    if (time_last_activity.getElapsedTime() > CONNECT_TIME_OUT) {
        return false;
    } 
    if (time_last_activity.getElapsedTime() > PING_TIME_OUT) {
        send(message::ping, message::to);
    }
    return true;
}

void user::restart_time_last_activity() {
    time_last_activity.restart();
}
