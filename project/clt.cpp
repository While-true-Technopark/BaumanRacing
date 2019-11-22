#include <SFML/Network.hpp>
#include <string>
#include <iostream>

size_t port = 5555;
std::string ip_local_host = "127.0.0.1";

class client {
 public:
    client(size_t port, const std::string& ip = ip_local_host)
        : port{port}
        , ip{ip}

    {
        if (socket.connect(ip_local_host, port) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
    }
    
    void run() {
        std::string msg = " hello from clt ";
        socket.send(msg.c_str(), msg.size() + 1);
    
        char buff[1024];
        std::size_t received = 0;
        socket.receive(buff, sizeof(buff), received);
        std::cout << buff << std::endl;
    }
    
    ~client() {}

 private:
     size_t port;
     std::string ip;
     sf::TcpSocket socket;
};

int main() {
    client clt(port);
    clt.run();
    return 0;
}
