#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "input_abst.hpp"

class input_manager : public base_manager {
 public:
    input_manager(input_abst *abst);
    int on_event(const event & e);
    input_abst *module;
};

#endif // INPUT_MANAGER_H_
