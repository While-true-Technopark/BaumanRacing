#include "renderer_manager.hpp"

renderer_manager::renderer_manager(renderer_abst *abst) {
    module = abst;
    my_client_id = -1;
    first_update_pos = true;
}

renderer_manager::~renderer_manager() {
    delete module;
}

int renderer_manager::handle_event(const event & e) {
    switch (e.type) {
        case textures_loaded: {
            std::vector<sf::Texture*> cars_textures(e.data.textures.players.begin(), e.data.textures.players.end());
            std::vector<sf::Music*> soundtracks(e.data.textures.soundtracks.begin(), e.data.textures.soundtracks.end());
            module->init({
                cars_textures,
                soundtracks,
                e.data.textures.map,
                e.data.textures.logo,
                e.data.textures.box,
                e.data.textures.arrow,
                e.data.textures.main_font
            });
            break;
        }
        case main_menu: {
            module->main_menu(e.data.box.select);
//            module->end_game_menu(56);
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
        case users: {
            module->users(e.data.box.select);
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
        case bad_name: { // окно ошибки
            module->show_bad();
            break;
        }
        case game_start: {
            my_client_id = e.data.box2.select;
            module->update_id(e.data.box2.id1, e.data.box2.id2, e.data.box2.id3, e.data.box2.id4);
            //game_render_data data = { };
            //module->build_game_scene(data);
            //module->build_start_scene(data);
            break;
        }
        case game_end: {
            module->end_game_menu(e.data.game_end.position);
            first_update_pos = true;
            break;
        }
        case update_position: {
            game_render_data data = { };
            for (int i = 0; i != data.players.size(); i++) {
                data.players[i].position = e.data.players_positions.player[i];
            }
            std::swap(data.players[0], data.players[my_client_id]);
            if (first_update_pos) {
                first_update_pos = false;
                module->build_start_scene(data);
            } else {
                module->build_game_scene(data);
            }
            break;
        }
        default:
            return RNDR_MNGR_WRONG_EVENT_TYPE;
    }
    return RNDR_MNGR_OK;
}
