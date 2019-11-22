#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//namespace srv {
    
size_t port = 5555;
std::string ip_local_host = "127.0.0.1";
size_t max_clients = 4;

class server {
 public:
    server(size_t port, const std::string& ip = ip_local_host, size_t max_clients = max_clients)
        : port{port}
        , ip{ip}
        , max_clients{max_clients}
    {
        if (listener.listen(port) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
       
        // listener.setBlocking(false); // non-blocking sockets
    }
    
    void run() {
        for (size_t i = 0; i < max_clients) {
            fork();
        }
            
        sf::TcpSocket socket;
        if (listener.accept(socket) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
        
        char buff[1024];
        std::size_t received = 0;
        socket.receive(buff, sizeof(buff), received);
        std::cout << buff << std::endl;
        
        std::string msg = " hello from srv ";
        socket.send(msg.c_str(), msg.size() + 1);
        
        for (size_t i = 0; i < max_clients; i++) {
            int status = 0;
            wait(&status);
            if (!WIFEXITED(status)) {
                exit(EXIT_FAILURE);
            }
        }

    }
    
    ~server() {
        listener.close();
    }
    
 private:
     size_t port;
     std::string ip;
     size_t max_clients;
     sf::TcpListener listener;
};

// }

int main() {

    /*server srv(port);
    srv.run();*/
    return 0;
}
