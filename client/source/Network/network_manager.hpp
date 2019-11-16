#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "network_abst.hpp"

class network_manager : public base_manager {
 public:
    network_manager(network_abst *abst);
    int on_event(const event & e);
    network_abst *module;
};

#endif // NETWORK_MANAGER_H_
