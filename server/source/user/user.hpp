#ifndef USER_H_
#define USER_H_

#include "message.hpp"

class user final {
 public:
    user();
    // поч с этим при линковке ругается на unique_ptr?
    //virtual ~user() = default;
    //user(const user&) = delete;
    //user& operator=(const user&) = delete;
    
    void send(message::header _header, const std::string body);
    json receive();
    sf::TcpSocket& get_socket();
    bool ping();
    void restart_time_last_activity();
    
 private:
    std::unique_ptr<sf::TcpSocket> socket;
    sf::Clock time_last_activity;
};

#endif  // USER_H_
