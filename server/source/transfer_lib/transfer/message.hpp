#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "command.hpp"

class message {
 public:
    enum header {
        // from clt to srv (->) 
        // from srv to clt (<-)
        
        // guest
        create,     // ->
        join,       // ->
        status,     // <-
        
        // before game
        setting,    // ->
        wait,       // <-
        start,      // <-
        
        // game
        command,   // ->
        coord,   // <-
        coord_s,   // <-
        rating,    // <-
        
        // after game
        finish,    // <-
        
        // shared
        ping,      // <-->
    };
    
    static const std::string head;
    static const std::string body;
    
    static const std::string ok;
    static const std::string fail;

    static const std::string to;
    static const std::string back;
    
    static json packet_to_json(sf::Packet& packet);
    static sf::Packet json_to_packet(json& msg);
    static json get_message(header _header);
    
 private:
    // guest
    static json message_init(header _header);
    static json message_status();
    
    // before game
    static json message_setting();
    static json message_wait();
    static json message_start();
    
    // game
    static json message_command();
    static json message_coord();
    static json message_coord_s();
    static json message_rating();
    
    // after game
    static json message_finish();
    
    // shared
    static json message_ping();
};

#endif  // MESSAGE_H_
