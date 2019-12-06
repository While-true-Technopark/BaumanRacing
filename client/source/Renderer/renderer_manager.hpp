#ifndef RENDERER_MANAGER_H_
#define RENDERER_MANAGER_H_

#include "base_manager.hpp"
#include "event.hpp"
#include "renderer_abst.hpp"

class renderer_manager : public base_manager {
 public:
    explicit renderer_manager(renderer_abst *abst);
    int handle_event(const event & e) override;
    renderer_abst *module;
 private:
    int my_client_id;
};

#endif  // RENDERER_MANAGER_H_
