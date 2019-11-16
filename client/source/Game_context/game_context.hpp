#ifndef GAME_CONTEXT_H_
#define GAME_CONTEXT_H_

#include "game_context_abst.hpp"
#include "event.hpp"

class game_context : public game_context_abst {
 public:
    int get_name_from_id(size_t id);
    int get_car_from_id(size_t id);
    int add_players(struct players_info);
 private:
    event positions;
    event players;
};

#endif // GAME_CONTEXT_H_
