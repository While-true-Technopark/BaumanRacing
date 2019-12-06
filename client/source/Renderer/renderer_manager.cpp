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
                e.data.textures.player_3
            };
            module->init(cars_textures, e.data.textures.map, e.data.textures.logo, e.data.textures.box,
            e.data.textures.arrow, e.data.textures.main_font);
            break;
        }
        case main_menu: {
            module->main_menu(e.data.box.select);
            break;
        }
        case connect_to_open: { // окно выбора
            module->connect_to_open(e.data.box.select);
            break;
        }
        case create_room: { // новая комната
             module->create_room(&e.data.input_ev.str);
             break;
        }
        case connect_to_room: { // существующая
             module->connect_to_room(&e.data.input_ev.str);
             break;
        }
        case show_car: { // окно выбора машинки
             module->show_car(e.data.box.select);
             break;
        }
        case waiting: { // окно ожидания
            module->show_wait(e.data.box.select);
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
