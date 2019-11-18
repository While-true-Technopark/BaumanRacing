#ifndef BASE_MANAGER_H_
#define BASE_MANAGER_H_

#include "event.hpp"

class base_manager {
 public:
    virtual int handle_event(const event & e) = 0;
};

#endif  // BASE_MANAGER_H_
