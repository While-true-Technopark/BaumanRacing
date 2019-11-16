#ifndef NETWORK_H_
#define NETWORK_H_

#include "event.hpp"
#include "network_abst.hpp"
#include "event_throwable.hpp"

class network : public network_abst {
 public:
    event get_last_package();
    void keys_send(struct keys_pressed);
    void name_car_send(struct player_info);
};

#endif // NETWORK_H_
