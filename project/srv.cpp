#include <memory>
#include "network_data.hpp"

//namespace srv {
    
// TODO: обработка исключений
// TODO: написать обработчики событий

class clients_room {
 public:
    clients_room(std::unique_ptr<sf::TcpSocket>&& first_clt, sf::SocketSelector& selector, size_t max_clients = MAX_CLTS)
        : selector{selector}
        , max_clients{max_clients}
    {
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
};

class server {
 public:
    server(size_t port = PORT, const std::string& ip = LOCAL_IP, size_t max_clients = MAX_CLTS)
        : max_clients{max_clients}
    {
        if (listener.listen(port, ip) != sf::Socket::Done) {
            // throw std::runtime_error(std::strerror(errno));
        }
        selector.add(listener);
        std::cout << "server is started and waiting for clients" << std::endl;
    }
    
    void run() {
        while (true) {
            if (selector.wait(TIME_OUT)) {
                if (selector.isReady(listener)) {
                    std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
                    if (listener.accept(*client) == sf::Socket::Done) {
                        selector.add(*client);
                        guests.emplace_back(std::move(client));
                        std::cout << "add guest" << std::endl;
                    } else {
                        // throw
                    }
                } else {
                    rooms_event_handler();
                    guests_event_handler();
                }
            } else {
                ping_rooms();
                ping_guests();
            }
        }
    }
    
    virtual void rooms_event_handler() {
        for(auto& room : rooms) {
            room.second.event_handler();
        }
    }
    
    virtual void guests_event_handler() {
        for (size_t idx = 0; idx < guests.size(); ++idx) {
            std::unique_ptr<sf::TcpSocket>& clt = guests[idx];
            if (selector.isReady(*clt)) {
                sf::Packet packet;
                clt->receive(packet);
                json msg = message::packet_to_json(packet);
                auto head = msg[message::head];
                if (head == message::CREATE) {
                    send_status(clt, true);
                    std::string room_name = msg[message::body];
                    rooms.emplace(room_name, clients_room(std::move(clt), selector, max_clients));
                    std::cout << "room " << room_name << " created" << std::endl; // TODO: logger
                } else if (head == message::JOIN) {
                    send_status(clt, true);
                    std::string room_name = msg[message::body];
                    rooms.at(room_name).add_client(std::move(clt));
                    std::cout << "client joined in room " << room_name << std::endl; // TODO: logger
                    //send_status(clt, false);
                } else {
                    send_status(clt, false);
                    selector.remove(*clt);
                    std::cout << "fail in massage" << std::endl; // TODO: logger
                }
                guests.erase(guests.begin() + idx);
                --idx;
            }
        }
    }
    
    virtual void ping_guests() {
        std::cout << "ping guests" << std::endl; // TODO: logger
    }
    virtual void ping_rooms() {
        std::cout << "ping rooms" << std::endl; // TODO: logger
    }
    /*virtual void ping_guests() {
        for (size_t idx = 0; idx < guests.size(); ++idx) {
            std::unique_ptr<sf::TcpSocket>& clt = guests[idx];
            json msg = message::get_message(message::WAIT);
            sf::Packet packet = message::json_to_packet(msg);
            clt->send(packet);
            std::cout << "send ping" << std::endl;
            packet.clear();
            if (clt->receive(packet) != sf::Socket::Done) {
                std::cout << "fail ping" << std::endl;
            }
            json res = message::packet_to_json(packet);
            if (msg != res) {
                std::cout << "fail ping" << std::endl;
            }
            std::cout << "receive ping" << std::endl;
            if ( != sf::Socket::Done) {
                std::cout << "client shut down" << std::endl; // TODO: logger
                selector.remove(*clt);
                guests.erase(guests.begin() + idx);
                --idx;
            } else {
                std::cout << packet;
                std::cout << "ping sent" << std::endl; // TODO: logger
            }
        }
    }*/

    
    ~server() {
        listener.close();
    }
    
 private:
    const size_t max_clients;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::map<std::string, clients_room> rooms;
    std::vector<std::unique_ptr<sf::TcpSocket>> guests; // клиенты, которые пока без комнаты
     
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
