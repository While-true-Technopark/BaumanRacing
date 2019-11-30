#ifndef NETWORK_ABST_H_
#define NETWORK_ABST_H_

#include <SFML/Graphics.hpp>

class network_abst {
 public:
    virtual event get_last_package() = 0;
    virtual void keys_send(struct keys_pressed) = 0;
    virtual void name_car_send(struct player_info) = 0;
    virtual struct players_positions_info get_positions() = 0;
    struct players_positions_info positions;
};

#endif  // NETWORK_ABST_H_
