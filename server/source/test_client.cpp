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
        }
    }
    
    ~client() {}

 private:
    sf::TcpSocket socket;
    
    bool init() {
        
        json msg;
        
        // TODO: прикрутить норм меню (Слава)
        {
            std::cout << "create a room (0), join the room (1): ";
            bool tmp = false;
            std::cin >> tmp;
        
            std::cout << "print name room: ";
            std::string room_name;
            std::cin >> room_name;
       
            if (!tmp) {
                msg = message::get_message(message::create);
            } else {
                msg = message::get_message(message::join);
            }
        
            msg[message::body] = room_name;
        }
        
        sf::Packet packet = message::json_to_packet(msg);
        socket.send(packet);
        packet.clear();
        
        // цикл потому что он может получить тут ping
        while (true) {
            socket.receive(packet);
            msg = message::packet_to_json(packet);
            if (msg[message::head] == message::status) {
                break;
            }
            if (msg[message::head] == message::ping && msg[message::body] == message::to) {
                msg = message::get_message(message::ping);
                msg[message::body] = message::back;
                packet = message::json_to_packet(msg);
                socket.send(packet);
                std::cout << "send on ping" << std::endl; // TODO: logger
            }
            packet.clear();
        }
        
        return msg[message::body] == message::ok;
    }
};

int main() {
    client clt(PORT, LOCAL_IP);
    clt.run();
    return 0;
}
