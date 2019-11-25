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
        // TODO: прикрутить норм меню
        std::cout << "create a room (0), join the room (1): ";
        bool tmp = false;
        std::cin >> tmp;
        
        std::string room_name;
        std::cout << "print name room: ";
        std::getline(std::cin, room_name);
        
        json msg;
        if (!tmp) {
            msg = message::get_message(message::CREATE);
        } else {
            msg = message::get_message(message::JOIN);
        }
        msg[message::body] = room_name;
        sf::Packet packet = message::json_to_packet(msg);
        socket.send(packet);
        packet.clear();
        
        socket.receive(packet);
        msg = message::packet_to_json(packet);
        
        if (msg[message::head] == message::STATUS && msg[message::body]) {
            std::cout << "connection to server established" << std::endl; // TODO: logger
        } else {
            std::cout << "connection to server not established" << std::endl;
        }
        
        /*std::string msg = " hello from clt ";
        socket.send(msg.c_str(), msg.size() + 1);
    

        
        while (true) {
            char buff[1024];
            std::size_t received = 0;
            socket.receive(buff, sizeof(buff), received);
            std::cout << buff << std::endl;
            
            std::getline(std::cin, msg);
            socket.send(msg.c_str(), msg.size() + 1);
        }*/
    }
    
    ~client() {}

 private:
     size_t port;
     std::string ip;
     sf::TcpSocket socket;
};

int main() {
    client clt(PORT);
    clt.run();
    return 0;
}
