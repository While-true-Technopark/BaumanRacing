#ifndef NETWORK_H_
#define NETWORK_H_

#include "event.hpp"
#include "network_abst.hpp"

class network : public network_abst {
 public:
    network();
    ~network();
    event get_last_package();
    void keys_send(struct keys_pressed);
    void name_car_send(struct player_info);
    struct players_positions_info get_positions();
    bool connect(size_t port, const std::string& ip);
    int create_room(const char (*str)[256], int box);
    int join_room(const char (*str)[256]);
    int connect_room(const char (*str)[256]);
    int set_car(size_t index);
    void ping();
    json get();
    int close();
    void run();
    template<class type>
    void send(message::header head, const type& body);
    struct keys_pressed keys;
    float speed;
 private:
    sf::TcpSocket socket;
};

#endif  // NETWORK_H_
