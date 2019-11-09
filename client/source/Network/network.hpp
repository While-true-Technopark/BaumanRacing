#ifndef NETWORK_H_
#define NETWORK_H_

#include "event.hpp"
#include "base_module.hpp"
#include "event_throwable.hpp"

class network : public base_module, event_throwable {
 public:
    int on_event(const event & e);
    event get_last_package();
    event throw_event();
};

#endif // NETWORK_H_
