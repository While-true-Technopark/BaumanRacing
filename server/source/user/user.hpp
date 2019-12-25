#ifndef USER_H_
#define USER_H_

#include "message.hpp"

class user final {
 public:
    user();
    template<class type>
    void send(message::header head, const type& body) const {
        json msg = message::get_message(head);
        msg[message::body] = body;
        sf::Packet packet = message::json_to_packet(msg);
        socket->send(packet);
    }
    json receive() const;
    bool ping() const;
    sf::TcpSocket& get_socket();
    void restart_tla();
    
 private:
    std::unique_ptr<sf::TcpSocket> socket;
    sf::Clock time_last_activity;
};

#endif  // USER_H_
