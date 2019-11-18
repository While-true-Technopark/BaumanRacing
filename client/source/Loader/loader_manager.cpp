#include "loader_manager.hpp"

loader_manager::loader_manager(loader_abst* abst) {
    module = abst;
}

int loader_manager::handle_event(const event& e) {
    switch(e.type) {
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
    return e;
}