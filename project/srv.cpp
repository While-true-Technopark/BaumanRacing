#include <memory>
#include "network_data.hpp"

//namespace srv {
    
// TODO: обработка исключений
// TODO: написать обработчики событий

struct client {
    std::unique_ptr<sf::TcpSocket> socket;
    sf::Clock clock; // time after last activity
    
    client() 
        : socket{std::make_unique<sf::TcpSocket>()}
    {}
    
    void send(message::header _header, const std::string body) {
        json msg = message::get_message(_header);
        msg[message::body] = body;
        sf::Packet packet = message::json_to_packet(msg);
        socket->send(packet);
    }
    
    bool ping() {
        if (clock.getElapsedTime() > 3.0f * TIME_OUT) {
            return false;
        } 
        if (clock.getElapsedTime() > TIME_OUT) {
            send(message::ping, "to");
        }
        return true;
    }
};

class clients_room {
 public:
    clients_room(client&& first_clt, sf::SocketSelector& selector, size_t max_clients = MAX_CLTS)
        : selector{selector}
        , max_clients{max_clients}
    {
        clients.emplace_back(std::move(first_clt));
    }
    
    virtual void event_handler() {
        for (size_t idx = 0; idx < clients.size(); ++idx) {
            client& clt = clients[idx];
            if (selector.isReady(*(clt.socket))) {
            }
        }
    }
    
    bool add_client(client&& clt) {
        if (clients.size() < max_clients) {
            clients.emplace_back(std::move(clt));
            return true;
        }
        return false;
    }
        
 private:
    sf::SocketSelector& selector;
    const size_t max_clients;
    std::vector<client> clients;
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
                    add_guest();
                } else {
                    rooms_event_handler();
                    guests_event_handler();
                }
            }
            ping_rooms();
            ping_guests();
        }
    }
    
    virtual void rooms_event_handler() {
        for(auto& room : rooms) {
            room.second.event_handler();
        }
    }
    
    virtual void guests_event_handler() {
        for (size_t idx = 0; idx < guests.size(); ++idx) {
            client& clt = guests[idx];
            if (selector.isReady(*(clt.socket))) {
                sf::Packet packet;
                clt.socket->receive(packet);
                clt.clock.restart();
                json msg = message::packet_to_json(packet);
                auto head = msg[message::head];
                if (head == message::create) {
                    clt.send(message::status, "ok");
                    std::string room_name = msg[message::body];
                    rooms.emplace(room_name, clients_room(std::move(clt), selector, max_clients));
                    std::cout << "room " << room_name << " created" << std::endl; // TODO: logger
                } else if (head == message::join) {
                    clt.send(message::ping, "ok");
                    std::string room_name = msg[message::body];
                    rooms.at(room_name).add_client(std::move(clt));
                    std::cout << "client joined in room " << room_name << std::endl; // TODO: logger
                } else if (head == message::ping) {
                    if (msg[message::body] == "to") {
                        clt.send(message::ping, "back");
                    }
                } else {
                    clt.send(message::ping, "fail");
                    selector.remove(*(clt.socket));
                    std::cout << "fail in massage" << std::endl; // TODO: logger
                }
                guests.erase(guests.begin() + idx);
                --idx;
            }
        }
    }
    
    void ping_guests() {
        for (size_t idx = 0; idx < guests.size(); ++idx) {
            std::cout << "ping guest " << idx << std::endl; // TODO: logger
            client& clt = guests[idx];
            if (!clt.ping()) {
                std::cout << "disconnect guest " << idx << std::endl; // TODO: logger
                selector.remove(*(clt.socket));
                guests.erase(guests.begin() + idx);
                --idx;
            }
        }
    }
    
    void ping_rooms() {
        std::cout << "ping rooms" << std::endl; // TODO: logger
    }
    
    ~server() {
        listener.close();
    }
    
 private:
    const size_t max_clients;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::map<std::string, clients_room> rooms;
    std::vector<client> guests; // клиенты, которые пока без комнаты
    
    bool add_guest() {
        client clt;
        if (listener.accept(*(clt.socket)) == sf::Socket::Done) {
            selector.add(*(clt.socket));
            guests.emplace_back(std::move(clt));
            std::cout << "add guest" << std::endl;
            return true;
        }
        return false;
    }
};

// }

int main() {
    server srv(PORT);
    srv.run();
    return 0;
}
