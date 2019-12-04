#include "loader_manager.hpp"

loader_manager::loader_manager(loader_abst* abst) {
    module = abst;
}

int loader_manager::handle_event(const event& e) {
    switch (e.type) {
        case application_run:
            // module->load_all();
            break;
        default:
            return -1;
    }
    return 0;
}

event loader_manager::throw_event() {
    event e;
    e.type = textures_loaded;

    while (!module->is_loaded()) {
        std::cout << "Loading...";
    }
    std::cout << "\n+++++++++++++++++++++Loaded+++++++++++++++++++++\n" << std::endl;

    e.data.textures.map = module->get_texture("map.png");
    e.data.textures.player_1 = module->get_texture("car_red.png");
    e.data.textures.player_2 = module->get_texture("car_blue.png");
    e.data.textures.player_3 = e.data.textures.player_1;
    e.data.textures.player_4 = e.data.textures.player_2;

    return e;
}
