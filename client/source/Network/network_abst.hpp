#ifndef NETWORK_ABST_H_
#define NETWORK_ABST_H_

#include "message.hpp"
#include <SFML/Graphics.hpp>

class network_abst {
 public:
    virtual event get_last_package() = 0;
    virtual void keys_send(struct keys_pressed) = 0;
    virtual void name_car_send(struct player_info) = 0;
    virtual struct players_positions_info get_positions() = 0;
    virtual bool connect(size_t port, const std::string& ip) = 0;
    virtual int create_room(const char (*str)[256], int box) = 0;
    virtual int join_room(const char (*str)[256]) = 0;
    virtual json get() = 0;
    virtual int set_car(size_t index) = 0;
    virtual void ping() = 0;
    virtual int close() = 0;
    struct players_positions_info positions;
};

#endif  // NETWORK_ABST_H_
