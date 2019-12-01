#ifndef USER_H_
#define USER_H_

#include <memory>
#include "message.hpp"

const sf::Time PING_TIME_OUT = sf::seconds(30.0f);
const sf::Time CONNECT_TIME_OUT = 3.0f * PING_TIME_OUT;

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
