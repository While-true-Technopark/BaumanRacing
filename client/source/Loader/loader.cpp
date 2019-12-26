#include "loader.hpp"

loader::loader() {
    static_dir = "static/";
    loaded = false;
    sound_loaded = false;
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
    sounds_paths = {
        "menu_theme.ogg",
        "race_theme.ogg"
    };
    sounds = std::vector<sf::Music>(sounds_paths.size());
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

sf::Music* loader::get_sound(const std::string & name) {
    if (name == "menu_theme.ogg") {
        if (load_thread->joinable()) {
            while(!sound_loaded) {}
        }
        sounds[0].setLoop(true);
        sounds[0].play();
        sounds[0].setPlayingOffset(sf::seconds(22.f));
        return &sounds[0];
    }
    if (name == "race_theme.ogg") {
        sounds[1].setLoop(true);
        return &sounds[1];
    }
    return nullptr;
}

bool loader::is_loaded() {
    return loaded;
}

int loader::load_all_static() {
    std::cout << "Static loading..." << std::endl;
    for (size_t i = 0; i != sounds_paths.size(); i++) {
        if (!sounds[i].openFromFile(static_dir + sounds_paths[i])) {
            return LDR_FILE_NOT_LOADED;
        }
    }
    sound_loaded = true;
    for (auto& path : textures_paths) {
        sf::Texture texture;
        if (!texture.loadFromFile(static_dir + path)) {
            return LDR_FILE_NOT_LOADED;
        }
        texture.setSmooth(true);
        textures.emplace(std::make_pair(path, texture));
    }
    for (size_t i = 0; i != fonts_paths.size(); i++) {
        sf::Font font;
        if (!font.loadFromFile(static_dir + fonts_paths[i])) {
            return LDR_FILE_NOT_LOADED;
        }
        fonts.push_back(font);
    }
    std::cout << "Static loaded" << std::endl;

    loaded = true;
    return LDR_OK;
}
