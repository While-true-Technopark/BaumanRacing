#include "message.hpp"

const std::string message::head = "head";
const std::string message::body = "body";

const std::string message::room_name = "room_name";
const std::string message::size = "size";

const std::string message::id = "id";
const std::string message::settings = "settings";

const std::string message::ok = "ok";
const std::string message::fail = "fail";

const std::string message::to = "to";
const std::string message::back = "back";

json message::packet_to_json(sf::Packet& packet) {
    std::string tmp;
    packet >> tmp;
    try {
        return json::parse(tmp);
    } catch (json::parse_error& e) {
        return message_close();
    }
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
            return message_create();
        }
        case join: {
            return message_join();
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
        case pos: {
            return message_pos();
        }
        case pos_s: {
            return message_pos_s();
        }
        case rating: {
            return message_rating(rating);
        }
        case finish:  {
            return message_rating(finish);
        }
        
        case ping: {
             return message_ping();   
        }
        case close: {
             return message_close();   
        }
        
        default: {
            return json();
        }
    }
}

// TODO: авторизация: имя пользователя, пароль
json message::message_create() {
    return json{{head, create}, {body, json{{room_name, "name"}, {size, 4}}}}; // body - имя комнаты, размер
}

json message::message_join() {
    return json{{head, join}, {body, "room name"}}; // body - имя комнаты
}

json message::message_status() {
    return json{{head, status}, {body, ok}}; // body - ok, fail
}

json message::message_setting() {
    return json{{head, setting}, {body, game_object_type::medium}}; // body - small, medium, big
}

// TODO: вместо кол-ва присоед игроков писать их имена
json message::message_wait() {
    return json{{head, wait}, {body, 0}}; // body - кол-во присоед игроков
}

json message::message_start() {
    // return json{{head, start}, {body, json{{settings, std::vector<game_object_type>()}, {id, 0}}}}; 
    // body - настройки остальных игроков, личный номер в этом векторе [0,..., MAX_USERS)
    return json{{head, start}, {body, 0}}; // body - игровой номер [0,..., MAX_USERS)
}

json message::message_command() {
    move_command comm;
    return json{{head, command}, {body, comm.get_json()}}; // body - команды передвижения машинки в формате json
}

json message::message_pos() {
    return json{{head, pos}, {body, std::vector<position>()}}; // body - координаты всех игроков
}

json message::message_pos_s() {
    return json{{head, pos_s}, {body, std::vector<position>()}}; // body - координаты сторонних объектов
}

json message::message_rating(header _header) { // _header - rating, finish
    return json{{head, _header}, {body, std::vector<size_t>()}}; // body - рейтинг игроков
}

json message::message_ping() {
    return json{{head, ping}, {body, back}}; // body - to, back
    // to - нас пингуют (нужно ответить, иначе соединение будет разорвано)
    // back - нам ответили на пинг (можно ничего не отвечать)
}

json message::message_close() {
    return json{{head, close}, {body, EXIT_SUCCESS}}; // body - статус выхода
}
