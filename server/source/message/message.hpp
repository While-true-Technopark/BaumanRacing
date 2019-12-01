#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class message {
 public:
    enum header {
        create,
        join,
        status,
        ping,
        get_setting,
        set_setting,
        wait,
        start,
        stop,
    };
    
    /*inline*/ static const std::string head;/* = "head";*/
    /*inline*/ static const std::string body;/* = "body";*/
    
    static const std::string ok;
    static const std::string fail;
    static const std::string to;
    static const std::string back;
    
    static json packet_to_json(sf::Packet& packet);
    static sf::Packet json_to_packet(json& msg);
    static json get_message(header _header);
    
 private:
    static json message_init(header _header);
    static json message_wait();
    static json message_status();
    static json message_ping();
};

#endif  // MESSAGE_H_
