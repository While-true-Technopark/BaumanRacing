#include "message.hpp"

const std::string message::head = "head";
const std::string message::body = "body";

const std::string message::ok = "ok";
const std::string message::fail = "fail";

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
        case start: {
            return message_start();
        }
        
        case command: {
            return message_command();
        }
        case coord: {
            return message_coord();
        }
        case coord_s: {
            return message_coord_s();
        }
        case rating: {
            return message_rating();
        }
        
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
    return json{{head, setting}, {body, car_type::medium}}; // body - small, medium, big
}

json message::message_wait() {
    return json{{head, wait}, {body, 0}}; // body - кол-во присоед игроков
    // TODO: вместо кол-ва присоед игроков писать их имена
}

json message::message_start() {
    return json{{head, start}, {body, 0}}; // body - игровой номер [0,..., MAX_USERS)
}

json message::message_command() {
    move_command comm;
    return json{{head, command}, {body, comm.get_json()}}; // body - команды передвижения машинки в формате json
}

json message::message_coord() {
    players_coord coords;
    coords.fill({0, 0});
    return json{{head, coord}, {body, std::move(coords)}}; // body - координаты всех игроков
}

json message::message_coord_s() {
    return json{{head, coord_s}, {body, std::vector<point>()}}; // body - координаты сторонних объектов
}

json message::message_rating() {
    players_rating ratings;
    ratings.fill(0);
    return json{{head, rating}, {body, std::move(ratings)}}; // body - рейтинг игроков
}

json message::message_ping() {
    return json{{head, ping}, {body, back}}; // body - to, back
    // to - нас пингуют (нужно ответить, иначе соединение будет разорвано)
    // back - нам ответили на пинг (можно ничего не отвечать)
}
