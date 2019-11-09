#ifndef GAME_CONTEXT_H_
#define GAME_CONTEXT_H_

#include "base_module.hpp"
#include "event.hpp"

class game_context : public base_module {
 public:
    int on_event(const event & e);
    int get_name_from_id();
    int get_car_from_id();
    int add_player();
 private:
    event positions;
    event players;
};

#endif // GAME_CONTEXT_H_
