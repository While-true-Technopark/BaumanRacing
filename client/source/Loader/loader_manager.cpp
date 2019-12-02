#include "loader_manager.hpp"

loader_manager::loader_manager(loader_abst* abst) {
    module = abst;
}

int loader_manager::handle_event(const event& e) {
    switch (e.type) {
        case application_run:
            module->load_all();
            break;
        default:
            return -1;
    }
    return 0;
}

event loader_manager::throw_event() {
    event e;
    e.type = textures_loaded;
    e.data.textures.map = module->get_texture("map");
    e.data.textures.map2 = module->get_texture("map2");

    e.data.textures.player_1 = module->get_car(0);
    e.data.textures.player_2 = module->get_car(1);
    e.data.textures.player_3 = module->get_car(2);
    e.data.textures.player_4 = module->get_car(3);

    return e;
}
