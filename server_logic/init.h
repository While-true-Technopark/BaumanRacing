#ifndef BAUMANRACING_INIT_H
#define BAUMANRACING_INIT_H

#include <vector>
#include <memory>
#include <SFML/Network.hpp>
#include "../network/server.h"
#include "../network/connection.h"
#include "../game_manager/game_manager.h"

class init {
public:
    void server_init();
    unsigned get_games_num();
    void create_game(unsigned player_id);
    void join_game(unsigned player_id);

private:
    std::vector<std::unique_ptr<connection>> waiting_connections;
    server server;
    std::vector<game_manager> games;
};


#endif //BAUMANRACING_INIT_H
