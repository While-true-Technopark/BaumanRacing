#include "network_data.hpp"

class client {
 public:
    client(size_t port = PORT, const std::string& ip = LOCAL_IP)
        : port{port}
        , ip{ip}

    {
        if (socket.connect(ip, port) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
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
    size_t port;
    std::string ip;
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
                msg = message::get_message(message::CREATE);
            } else {
                msg = message::get_message(message::JOIN);
            }
        
            msg[message::body] = room_name;
        }
        
        sf::Packet packet = message::json_to_packet(msg);
        socket.send(packet);
        packet.clear();
        
        socket.receive(packet);
        msg = message::packet_to_json(packet);
        return msg[message::head] == message::STATUS && msg[message::body];
    }
};

int main() {
    client clt(PORT);
    clt.run();
    return 0;
}
