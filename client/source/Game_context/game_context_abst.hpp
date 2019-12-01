#ifndef GAME_CONTEXT_ABST_H_
#define GAME_CONTEXT_ABST_H_

#include <SFML/Graphics.hpp>

class game_context_abst {
 public:
    virtual int get_name_from_id(size_t id) = 0;
    virtual int get_car_from_id(size_t id) = 0;
    virtual int add_players(struct players_info) = 0;
    virtual int update_positions(struct players_positions_info) = 0;
};

#endif  // GAME_CONTEXT_ABST_H_
