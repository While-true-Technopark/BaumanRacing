#ifndef BAUMANRACING_GAME_MANAGER_H
#define BAUMANRACING_GAME_MANAGER_H

#include "../game_logic/map.h"
#include "../network/connection.h"
#include <SFML/System.hpp>
#include <vector>

struct command {
    bool forward;
    bool back;
    bool right_turn;
    bool left_turn;
    bool throw_side_object;
    bool super_speed;
};

class game_manager {
public:
    void start_game();
    void stop_game();
    void game_builder(command comm, unsigned player_id);
    void add_connection(connection* conn);
    void transmit_all_data();
    std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();

    const unsigned MAX_PLAYERS;
    const unsigned GAME_WAIT_CONNECTION;
    const unsigned GAME_RUN;
    const unsigned GAME_END_SHOW_RESULTS;
private:
    map game_map;
    unsigned game_mode;
    std::vector<std::unique_ptr<connection>> game_connections;
    unsigned room_id;
    sf::Time clock;
};


#endif //BAUMANRACING_GAME_MANAGER_H
