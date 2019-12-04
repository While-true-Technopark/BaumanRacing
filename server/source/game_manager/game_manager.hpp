#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

//#include "game_logic.hpp"
#include "map.hpp"

class game_manager {
 public:
    game_manager();
 private:
    game_map map;
};

/*class game_manager {
 public:
    enum {players_coord, side_objects_coord, all_coord};
    explicit game_manager(const map& _map) : game_map(_map) {}
    virtual ~game_manager() {}
    void game_builder(const command& comm, size_t player_id) {
        if (comm.forward || comm.back || comm.right_turn
            || comm.left_turn || comm.run_sprint) {
            make_move(comm, player_id);
        }
        if (comm.throw_side_object) {
            throw_side_object(player_id);
        }
    }
    std::vector<point> get_coord(size_t whose_coord = all_coord) {
        switch (whose_coord) {
            case players_coord: {
                return get_players_coord();
            }
            case side_objects_coord: {
                return get_side_objects_coord();
            }
            default: {
                std::vector<point> coord = get_players_coord();
                std::vector<point> tmp = get_side_objects_coord();
                coord.insert(coord.end(), tmp.begin(), tmp.end());
                return coord;
            }
        }
    }

 private:
    map game_map;
    virtual void make_move(const command& comm, size_t player_id) = 0;
    virtual void throw_side_object(size_t player_id) = 0;
    virtual std::vector<point> get_players_coord() = 0;
    virtual std::vector<point> get_side_objects_coord() = 0;
};*/

#endif  // GAME_MANAGER_H_
