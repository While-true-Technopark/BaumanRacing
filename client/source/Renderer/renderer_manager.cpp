#include "renderer_manager.hpp"

renderer_manager::renderer_manager(renderer_abst *abst) {
    module = abst;
}

int renderer_manager::handle_event(const event & e) {
    switch (e.type) {
        case textures_loaded: {
            std::vector<sf::Texture*> cars_textures = {
                e.data.textures.player_1,
                e.data.textures.player_2,
                e.data.textures.player_3,
                e.data.textures.player_4,
            };
            module->init(cars_textures, e.data.textures.map);
            break;
        }
        case game_start: {
            struct player_data player = { };
            game_render_data data = { };
            data.players.push_back(player);
            data.players.push_back(player);
            data.players.push_back(player);
            data.players.push_back(player);

            module->build_game_scene(data);
            break;
        }
        case update_position: {
            struct player_data player = { };
            game_render_data data = { };

            player = { .position = e.data.players_positions.player_1 };
            data.players.push_back(player);

            player = { .position = e.data.players_positions.player_2 };
            data.players.push_back(player);

            player = { .position = e.data.players_positions.player_3 };
            data.players.push_back(player);

            player = { .position = e.data.players_positions.player_4 };
            data.players.push_back(player);

            module->build_game_scene(data);
            break;
        }
        default:
            return -1;
    }
    return 0;
}
