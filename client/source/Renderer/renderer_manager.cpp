#include "renderer_manager.hpp"

renderer_manager::renderer_manager(renderer_abst *abst) {
    module = abst;
}

int renderer_manager::handle_event(const event & e) {
    switch(e.type) {
        case textures_loaded: {
            module->create_map(e.data.textures.map_number, e.data.textures.map);
            break;
        }
        case game_start: {
            game_render_data data = {};
            module->build_game_scene(data);
            break;
        }
        default:
            return -1;
    }
    return 0;
}