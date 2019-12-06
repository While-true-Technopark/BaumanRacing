#include "message.hpp"
#include "server.hpp"

class client {
 public:
    client(size_t port, const std::string& ip) {
        if (socket.connect(ip, port) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
        // clt.setBlocking(false);
    }
    
    ~client() {
        json msg = message::get_message(message::close);
        sf::Packet packet = message::json_to_packet(msg);
        socket.send(packet);
    }
    
    void run() {
        if (init()) {
            std::cout << "connection to server established" << std::endl; // TODO: logger
            while (true) {
                /*
                sf::Packet pack;
                socket.send(pack);
                std::cout << received_msg.dump() << std::endl;
                */
            }
        } else {
            std::cout << "connection to server not established" << std::endl;// TODO: logger
            //while (true) {}
        }
    }
    
    template<class type>
    void send(message::header head, const type& body) {
        json msg = message::get_message(head);
        msg[message::body] = body;
        sf::Packet packet = message::json_to_packet(msg);
        socket.send(packet);
    }
    
    json receive() {
        sf::Packet packet;
        socket.receive(packet);
        return message::packet_to_json(packet);
    }

 private:
    sf::TcpSocket socket;
    
    bool init() {
        
        // TODO: прикрутить норм меню (Слава)
        {
            std::cout << "create a room (0), join the room (1): ";
            bool tmp = false;
            std::cin >> tmp;
        
            std::cout << "print name room: ";
            std::string room_name;
            std::cin >> room_name;
       
            if (!tmp) {
                send(message::create, room_name);
            } else {
                send(message::join, room_name);
            }
        }
        
        // цикл потому что он может получить тут ping
        while (true) {
            json msg = receive();
            if (msg[message::head] == message::status) {
                if (msg[message::body] != message::ok) {
                    return false;
                } else {
                    send(message::setting, car_type::small);
                    std::cout << "set car type" << std::endl; // TODO: logger
                    return true;
                }
            }
            if (msg[message::head] == message::ping && msg[message::body] == message::to) {
                send(message::ping, message::back);
                std::cout << "send on ping" << std::endl; // TODO: logger
            }
        }
    }
};

int main() {
    client clt(PORT, LOCAL_IP);
    clt.run();
    return 0;
}
