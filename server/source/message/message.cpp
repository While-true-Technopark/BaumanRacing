#include "message.hpp"

const std::string message::head = "head";
const std::string message::body = "body";

const std::string message::ok = "ok";
const std::string message::fail = "fail";

const std::string message::small = "small";
const std::string message::medium = "medium";
const std::string message::big = "big";

const std::string message::to = "to";
const std::string message::back = "back";

json message::packet_to_json(sf::Packet& packet) {
    std::string tmp;
    packet >> tmp;
    return json::parse(tmp);
}
    
sf::Packet message::json_to_packet(json& msg) {
    std::string tmp = msg.dump();
    sf::Packet packet;
    packet << tmp;
    return packet;
}

json message::get_message(header _header) {
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
        
        case setting: {
            return message_setting();
        }
        case wait: {
            return message_wait();
        }
        /*case start: {
            return 
        }*/
        
        
        
        case ping: {
             return message_ping();   
        }
        
        default: {
            return json();
        }
    }
}

json message::message_init(header _header) {
    return json{{head, _header}, {body, "room name"}}; // body - имя комнаты
    // TODO: авторизация: имя пользователя, пароль
}

json message::message_status() {
    return json{{head, status}, {body, ok}}; // body - ok, fail
}

json message::message_setting() {
    return json{{head, setting}, {body, medium}}; // body - small, medium, big
}

json message::message_wait() {
    return json{{head, wait}, {body, 0}}; // body - кол-во присоед игроков
    // TODO: вместо кол-ва присоед игроков писать их имена
}

json message::message_command() {
    return json{{head, command}, {body, ""}};
}

json message::message_coord() {
    std::array<std::array<double, 2>, 4> c{{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    return json{{head, coord}, {body, std::move(c)}}; // body - кол-во присоед игроков
}

json message::message_ping() {
    return json{{head, ping}, {body, back}}; // body - to, back
    // to - пинг этой тачки (на него нужно ответить, иначе соединение буде разорвано)
    // back - нам ответили на пинг (можно ничего не отвечать)
}
