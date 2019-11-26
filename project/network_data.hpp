#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const size_t PORT = 5555;
const std::string LOCAL_IP = "127.0.0.1";
const size_t MAX_CLTS = 4;
const sf::Time TIME_OUT = sf::seconds(10.0f);

class message {
 public:
    
    inline static const std::string head = "head";
    enum header {
        CREATE = 100,
        JOIN,
        EXIT,
        STATUS,
        WAIT,
        PING,
        GET_SETTING,
        SET_SETTING,
    };
    
    inline static const std::string body = "body";
    /*struct body_attr {
        inline static const std::string client_name = "client name";
        inline static const std::string room_name = "room name";
    };*/

    static json get_message(header _header) {
        switch (_header) {
            case CREATE: {
                return message_init(CREATE);
            }
            case JOIN: {
                return message_init(JOIN);
            }
            case STATUS: {
                return message_status();
            }
            case WAIT: {
                return message_wait();
            }
            default: {
                return json();
            }
        }
    }
    
    static json packet_to_json(sf::Packet& packet) {
        std::string tmp;
        packet >> tmp;
        return json::parse(tmp);
    }
    
    static sf::Packet json_to_packet(json& msg) {
        std::string tmp = msg.dump();
        sf::Packet packet;
        packet << tmp;
        return packet;
    }
    
 private:
    static json message_init(header _header) {
        return json{{head, _header}, {body, "zalupa"}}; // имя комнаты
        // TODO: авторизация: имя пользователя, пароль
        /*{body, {{body_attr::client_name, "dick"}, {body_attr::room_name, "zalupa"}}}*/ 
    }
    static json message_wait() {
        return json{{head, WAIT}, {body, 0}}; // кол-во присоед игроков
                                              // TODO: или имена присоединившихся игроков
    }
    static json message_status() {
        return json{{head, STATUS}, {body, false}};
    }
};
