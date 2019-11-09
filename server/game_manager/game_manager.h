#ifndef PROJECT_GAME_MANAGER_H_
#define PROJECT_GAME_MANAGER_H_

#include "game_logic.h"

class game_manager {
 public:
 	explicit game_manager(const map& _map) : game_map(_map) {};
 	virtual ~game_manager() {};
    void start_game();
    void stop_game();
    void game_builder(const command& comm, size_t player_id) {
    	if (comm.forward || comm.back || comm.right_turn || comm.left_turn || comm.run_sprint) {
    		make_move(comm, player_id);
    	}
    	if (comm.throw_side_object) {
    		throw_side_object(player_id);
    	}
    };
    std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();
 private:
 	map game_map;
 	virtual void make_move(const command& comm, size_t player_id) = 0;
 	virtual void throw_side_object(size_t player_id) = 0;
};

#endif  // PROJECT_GAME_MANAGER_H_
