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
    bool ping();
    void restart_time_last_activity();
    
    std::unique_ptr<sf::TcpSocket> socket;
 
 private:
    sf::Clock time_last_activity;
};

#endif  // USER_H_
