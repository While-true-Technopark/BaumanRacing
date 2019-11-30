#ifndef NETWORK_H_
#define NETWORK_H_

#include "event.hpp"
#include "network_abst.hpp"

class network : public network_abst {
 public:
    network();
    event get_last_package();
    void keys_send(struct keys_pressed);
    void name_car_send(struct player_info);
    struct players_positions_info get_positions();
    struct keys_pressed keys;
    float speed;
};

#endif  // NETWORK_H_
