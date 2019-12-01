#ifndef LOADER_MANAGER_H_
#define LOADER_MANAGER_H_

#include "base_manager.hpp"
#include "event.hpp"
#include "event_throwable.hpp"
#include "loader_abst.hpp"

class loader_manager : public base_manager, event_throwable {
 public:
    explicit loader_manager(loader_abst* abst);
    int handle_event(const event& e) override;
    event throw_event() override;
    loader_abst* module;
};

#endif  // LOADER_MANAGER_H_
