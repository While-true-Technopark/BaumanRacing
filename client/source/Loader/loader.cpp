#include "loader.hpp"

loader::loader() {
    textures_dir = "static/";
    loaded = false;
    paths = {
        "map.png",
        "car_red.png",
        "car_blue.png"
    };

    load_thread = std::thread(&loader::load_textures, this);
}

int loader::load_all() {
    if (loaded) {
        return 0;
    }
    // if (load_thread.joinable()) {
    //     load_thread.join();
    // }

    // loaded = true;
    return 0;
}

sf::Texture* loader::get_texture(const std::string & name) {
    if (load_thread.joinable()) {
        load_thread.join();
    }
    auto search = textures.find(name);
    if (search != textures.end()) {
        return &search->second;
    }
    return nullptr;
}

bool loader::is_loaded() {
    return loaded;
}

int loader::load_textures() {
    for (auto& path : paths) {
        sf::Texture texture;
        if (!texture.loadFromFile(textures_dir + path)) {
            return -1;
        }
        textures.emplace(std::make_pair(path, texture));
    }
    loaded = true;
    return 0;
}