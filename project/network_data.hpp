#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const size_t PORT = 5555;
const std::string LOCAL_IP = "127.0.0.1";
const size_t MAX_CLTS = 4;
const sf::Time TIME_OUT = sf::seconds(30.0f);

class message {
 public:
    
    inline static const std::string head = "head";
    enum header {
        create = 100,
        join,
        status,
        ping,
        get_setting,
        set_setting,
        wait,
        start,
        stop,
    };
    
    inline static const std::string body = "body";
    /*struct body_attr {
        inline static const std::string client_name = "client name";
        inline static const std::string room_name = "room name";
    };*/

    static json get_message(header _header) {
        switch (_header) {
            case create: {
                return message_init(create);
            }
            case join: {
                return message_init(join);
            }
            case status: {
                return message_status();
            }
            case wait: {
                return message_wait();
            }
            case ping: {
                
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
    }
    static json message_wait() {
        return json{{head, wait}, {body, 0}}; // кол-во присоед игроков
        // TODO: вместо кол-ва присоед игроков писать их имена
    }
    static json message_status() {
        return json{{head, status}, {body, "ok"}}; // ok, fail
    }
    
    static json message_ping() {
        return json{{head, ping}, {body, "back"}};
        // to - пинг этой тачки, на него нужно ответить иначе соединение буде разорвано
        // back - запрашиваемая тачка ответила на пинг. можно ничего не отвечать
    }
};
