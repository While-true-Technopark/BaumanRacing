#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "base_module.hpp"
#include "event_manager.hpp"
#include "renderer.hpp"
#include "game_context.hpp"
#include "input.hpp"
#include "loader.hpp"
#include "network.hpp"

class application : public base_module {
 public:
    virtual bool run();
    int on_event(const event & e);
    static application& get_instance();
 private:
    application() = default;
    event_manager event_mngr;
    renderer renderer_obj;
    game_context game_context_obj;
    input input_obj;
    loader loader_obj;
    network network_obj;
};

#endif // APPLICATION_H_
