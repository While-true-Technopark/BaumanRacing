#include "loader.hpp"

loader::loader() {
    loaded = false;
    textures_paths.push_back("static/map.png");
    textures_paths.push_back("static/car_red.png");
    textures_paths.push_back("static/car_blue.png");
    textures_paths.push_back("static/car_yellow.png");
    textures_paths.push_back("static/logo.png");
    textures_paths.push_back("static/box.png");
    textures_paths.push_back("static/arrow.png");
    
    fonts_paths.push_back("static/Menlo-Regular.ttf");
}

int loader::load_all() {
    if (loaded) {
        return 0;
    }
    for (size_t i = 0; i != textures_paths.size(); i++) {
        sf::Texture texture;
        texture.loadFromFile(textures_paths[i]);
        textures.push_back(texture);
    }
    
    for (size_t i = 0; i != fonts_paths.size(); i++) {
        sf::Font font;
        font.loadFromFile(fonts_paths[i]);
        fonts.push_back(font);
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
    if (name == "car_yellow") {
        return &textures[3];
    }
    if (name == "logo") {
        return &textures[4];
    }
    if (name == "box") {
        return &textures[5];
    }
    if (name == "arrow") {
        return &textures[6];
    }
    return nullptr;
}

sf::Font* loader::get_font(const std::string & name) {
    if (name == "Menlo") {
        return &fonts[0];
    }
    return nullptr;
}
