#include "loader.hpp"

loader::loader() {
    loaded = false;
    paths.push_back("static/map.png");
    paths.push_back("static/car_red.png");
    paths.push_back("static/car_blue.png");
}

int loader::load_all() {
    if (loaded) {
        return 0;
    }
    for (size_t i = 0; i != paths.size(); i++) {
        sf::Texture texture;
        texture.loadFromFile(paths[i]);
        textures.push_back(texture);
    }

    loaded = true;
    return 0;
}

sf::Texture* loader::get_texture(const std::string & name) {
    if (name == "map") {
        return &textures[0];
    }
    if (name == "car_red") {
        return &textures[1];
    }
    if (name == "car_blue") {
        return &textures[2];
    }
    return nullptr;
}
