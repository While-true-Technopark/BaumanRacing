#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "base_module.hpp"
#include "event.hpp"
#include <vector>

class event_manager {
public:
    std::vector<base_module *> get_event_modules();
private:
    std::vector<base_module *> modules;
};

#endif // EVENT_MANAGER_H
