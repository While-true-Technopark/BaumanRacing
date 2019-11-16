#ifndef GAME_CONTEXT_MANAGER_H_
#define GAME_CONTEXT_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "game_context_abst.hpp"

class game_context_manager : public base_manager {
 public:
    game_context_manager(game_context_abst *abst);
    int on_event(const event & e);
    game_context_abst *module;
};

#endif // GAME_CONTEXT_MANAGER_H_
