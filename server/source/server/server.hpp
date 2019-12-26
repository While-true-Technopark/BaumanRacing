#ifndef SERVER_H_
#define SERVER_H_

#include "users_room.hpp"

class server final {
 public:
    server(size_t port, const std::string& ip) noexcept;
    ~server();
    server() = delete;
    server(const server&) = delete;
    server& operator=(const server&) = delete;
    server(server&&) = delete;
    server& operator=(server&&) = delete;
    void run();
    void stop();
    json get_info() const;
    void rooms_event_handler();
    void guests_event_handler();
    
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
