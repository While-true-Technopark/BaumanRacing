#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "network_abst.hpp"
#include "event_throwable.hpp"
#include "message.hpp"

class network_manager : public base_manager, event_throwable {
 public:
    explicit network_manager(network_abst *abst);
    int handle_event(const event & e);
    event throw_event();
    network_abst *module;
};

#endif  // NETWORK_MANAGER_H_
