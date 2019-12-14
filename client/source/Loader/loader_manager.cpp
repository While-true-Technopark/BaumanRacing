#include "loader_manager.hpp"

loader_manager::loader_manager(loader_abst* abst) {
    module = abst;
}

loader_manager::~loader_manager() {
    delete module;
}

int loader_manager::handle_event(const event& e) {
    switch (e.type) {
        case application_run:
            module->load_all();
            break;
        default:
            return LDR_MNGR_WRONG_EVENT_TYPE;
    }
    return LDR_MNGR_OK;
}

event loader_manager::throw_event() {
    event e;
    e.type = textures_loaded;
    e.data.textures.logo = module->get_texture("logo.png");
    e.data.textures.main_font = module->get_font("Menlo");
    e.data.textures.box = module->get_texture("box.png");
    e.data.textures.arrow = module->get_texture("arrow.png");
    e.data.textures.players[0] = module->get_texture("red_taz.png");
    e.data.textures.players[1] = module->get_texture("blue_taz.png");
    e.data.textures.players[2] = module->get_texture("yellow_taz.png");
    e.data.textures.map = module->get_texture("map.png");
    return e;
}
