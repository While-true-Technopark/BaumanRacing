#include "loader.hpp"

loader::loader() {
    static_dir = "static/";
    loaded = false;
    textures_paths = {
        "map.png",
        "red_taz.png",
        "blue_taz.png",
        "yellow_taz.png",
        "logo.png",
        "box.png",
        "arrow.png"
    };
    fonts_paths = {
        "Menlo-Regular.ttf"
    };
    load_thread = nullptr;
}

loader::~loader() {
    delete load_thread;
}

int loader::load_all() {
    if (loaded) {
        return LDR_OK;
    }
    load_thread = new std::thread(&loader::load_all_static, this);
    return LDR_OK;
}

sf::Texture* loader::get_texture(const std::string & name) {
    if (load_thread->joinable()) {
        load_thread->join();
    }
    auto search = textures.find(name);
    if (search != textures.end()) {
        return &search->second;
    }
    std::cout << "texture not found" << std::endl;
    return nullptr;
}

sf::Font* loader::get_font(const std::string & name) {
    if (name == "Menlo") {
        return &fonts[0];
    }
    return nullptr;
}

bool loader::is_loaded() {
    return loaded;
}

int loader::load_all_static() {
    std::cout << "Textures loading..." << std::endl;
    for (auto& path : textures_paths) {
        sf::Texture texture;
        if (!texture.loadFromFile(static_dir + path)) {
            return LDR_FILE_NOT_LOADED;
        }
        textures.emplace(std::make_pair(path, texture));
    }
    for (size_t i = 0; i != fonts_paths.size(); i++) {
        sf::Font font;
        if (!font.loadFromFile(static_dir + fonts_paths[i])) {
            return LDR_FILE_NOT_LOADED;
        }
        fonts.push_back(font);
    }
    std::cout << "Textures loaded" << std::endl;

    loaded = true;
    return LDR_OK;
}
