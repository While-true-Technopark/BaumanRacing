#include <SFML/Network.hpp>
#include <string>
#include <iostream>

size_t PORT = 5550;
std::string LOCAL_IP = "127.0.0.1";

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
        std::string msg = " hello from clt ";
        socket.send(msg.c_str(), msg.size() + 1);
    

        
        while (true) {
            char buff[1024];
            std::size_t received = 0;
            socket.receive(buff, sizeof(buff), received);
            std::cout << buff << std::endl;
            
            std::getline(std::cin, msg);
            socket.send(msg.c_str(), msg.size() + 1);
        }
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
