#ifndef SERVER_H_
#define SERVER_H_

#include "users_room.hpp"

class server {
 public:
    server(size_t port, const std::string& ip) noexcept;
    void run();
    void stop();
    json get_info() const;
    virtual void rooms_event_handler();
    virtual void guests_event_handler();
    virtual ~server();
    
 private:
    bool start;
    sf::TcpListener listener;
    std::shared_ptr<sf::SocketSelector> selector;
    std::unordered_map<std::string, users_room> rooms;
    std::vector<user> guests; // клиенты, которые пока без комнаты
    bool add_guest();
    void ping_rooms();
    void ping_guests();
};

#endif  // SERVER_H_
