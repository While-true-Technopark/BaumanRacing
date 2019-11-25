#include <memory>
#include "network_data.hpp"

//namespace srv {
    


// TODO: обработка исключений
// TODO: написать класс massage
// TODO: написать обработчики событий
// TODO: написать разделение на комнаты

class clients_room {
 public:
    clients_room(std::unique_ptr<sf::TcpSocket>&& first_clt, sf::SocketSelector& selector, size_t max_clients = MAX_CLTS)
        : selector{selector}
        , max_clients{max_clients}
    {
        // selector.add(*client);
        clients.emplace_back(std::move(first_clt));
    }
    
    virtual void event_handler() {
        
    }
    
    bool add_client(std::unique_ptr<sf::TcpSocket>&& client) {
        if (clients.size() < max_clients || 
            std::find(clients.begin(), clients.end(), client) != clients.end()) {
            clients.emplace_back(std::move(client));
            return true;
        }
        return false;
    }
    
 private:
     sf::SocketSelector& selector;
     const size_t max_clients;
     std::vector<std::unique_ptr<sf::TcpSocket>> clients;
     /*
      game manager
      */
};

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
        std::cout << "Server is started. Waiting for clients" << std::endl;
    }
    
    void run() {
        while (true) {
            if (selector.wait()) {
                if (selector.isReady(listener)) {
                    // join or create
                    std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
                    if (listener.accept(*client) == sf::Socket::Done) {
                        selector.add(*client);
                        if (selector.isReady(*client)) {
                            sf::Packet packet;
                            client->receive(packet);
                            json msg = message::packet_to_json(packet);
                            auto head = msg[message::head];
                            if (head == message::CREATE) {
                                send_status(client, true);
                                rooms.emplace(msg[message::body], clients_room(std::move(client), selector, max_clients));
                                std::cout << "created" << std::endl; // TODO: logger
                            } else if (head == message::JOIN) {
                                send_status(client, true);
                                rooms.at(msg[message::body]).add_client(std::move(client));
                                std::cout << "joined" << std::endl; // TODO: logger
                            } else {
                                send_status(client, false);
                                selector.remove(*client);
                                std::cout << "fail in massage" << std::endl; // TODO: logger
                            }
                        } else {
                            send_status(client, false);
                            selector.remove(*client);
                            std::cout << "selector id not ready" << std::endl; // TODO: logger
                        }
                        
                    } else {
                        // throw
                    }
                } else {
                    for(auto& room : rooms) {
                        room.second.event_handler();
                    }
                }
            }
        }
    }
    
    ~server() {
        listener.close();
    }
    
 private:
    const size_t port;
    const std::string ip;
    const size_t max_clients;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::map<std::string, clients_room> rooms;
     
    void send_status(const std::unique_ptr<sf::TcpSocket>& clt, bool status) {
        json msg_status = message::get_message(message::STATUS);
        if (status) {
            msg_status[message::body] = true;
        }
        sf::Packet packet = message::json_to_packet(msg_status);
        clt->send(packet);
    }
};

// }

int main() {
    server srv(PORT);
    srv.run();
    return 0;
}
