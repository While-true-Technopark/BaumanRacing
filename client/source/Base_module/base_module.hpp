#ifndef BASE_MODULE_H_
#define BASE_MODULE_H_

#include "event.hpp"

class base_module {
 public:
    virtual int on_event(const event & e) = 0;
};

#endif  // BASE_MODULE_H_
