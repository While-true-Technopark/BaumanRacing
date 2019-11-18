#ifndef LOADER_MANAGER_H_
#define LOADER_MANAGER_H_

#include "base_manager.hpp"
#include "event.hpp"
#include "loader_abst.hpp"

class loader_manager : public base_manager {
 public:
    loader_manager(loader_abst *abst);
    int on_event(const event & e) override;
    loader_abst *module;
};

#endif // LOADER_MANAGER_H_
