#ifndef SERVER_H_
#define SERVER_H_

#include "users_room.hpp"


const size_t PORT = 5555;
const std::string LOCAL_IP = "127.0.0.1";

class server {
 public:
    server(size_t port, const std::string& ip);
    void run();
    virtual void rooms_event_handler();
    virtual void guests_event_handler();
    virtual ~server();
    
 private:
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::map<std::string, users_room> rooms;
    std::vector<user> guests; // клиенты, которые пока без комнаты
    bool add_guest();
    void ping_rooms();
    void ping_guests();
};

#endif  // SERVER_H_
