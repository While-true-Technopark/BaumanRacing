#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include <string>
#include <memory>

//namespace srv {
    
size_t PORT = 5550;
std::string LOCAL_IP = "127.0.0.1";
size_t MAX_CLTS = 4;

// TODO: обработка исключений

class server {
 public:
    server(size_t port = PORT, const std::string& ip = LOCAL_IP, size_t max_clients = MAX_CLTS)
        : port{port}
        , ip{ip}
        , max_clients{max_clients}
    {
        if (listener.listen(port) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
        selector.add(listener);
        // listener.setBlocking(false); // non-blocking sockets
        std::cout << "Server is started. Waiting for clients" << std::endl;
    }
    
    void run() {
        size_t clt_id = 0;
        while (true) {
            if (selector.wait()) {
                if (selector.isReady(listener)) {
                    std::shared_ptr<sf::TcpSocket> client = std::make_shared<sf::TcpSocket>();
                    // std::sf::TcpSocket client;
                    if (listener.accept(*client) == sf::Socket::Done) {
                        clients.push_back(client);
                        selector.add(*client);
                        ++clt_id;
                    } else {
                        // throw
                    }
                } else {
                    for(size_t id = 0; id < clients.size(); ++id) {
                        // TODO: написать класс massage
                        // TODO: написать обработчики событий
                        // TODO: написать разделение на комнаты
                        auto& curr_clt = *clients[id];
                        if (selector.isReady(curr_clt)) {
                            char buff[100];
                            size_t received = 0;
                            curr_clt.receive(buff, sizeof(buff), received);
                            std::cout <<  buff <<  " him id: " << id << std::endl;
                            
                            std::string msg;// = "hello from srv, your id: " + std::to_string(id);
                            puts(" print msg for clt: ");
                            // test: уронить клиента в этот момент и проверить не зависнет ли сервер на send
                            // все ок
                            std::getline(std::cin, msg);
                            curr_clt.send(msg.c_str(), msg.size() + 1);
                        }
                    }
                }
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
     sf::SocketSelector selector;
     std::vector<std::shared_ptr<sf::TcpSocket>> clients;
};

// }

int main() {
    server srv(PORT);
    srv.run();
    return 0;
}
