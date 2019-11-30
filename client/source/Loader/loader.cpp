#include "loader.hpp"

loader::loader() {
    loaded = false;
    paths.push_back("static/map_tiles.png");
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
    sf::Sprite car_red;
    car_red.setTexture(*get_texture("car_red"));
    car_red.setOrigin(get_texture("car_red")->getSize().x/2,
        get_texture("car_red")->getSize().y/2);

    sf::Sprite car_blue;
    car_blue.setTexture(*get_texture("car_blue"));
    car_blue.setOrigin(get_texture("car_blue")->getSize().x/2,
        get_texture("car_blue")->getSize().y/2);

    cars.push_back(car_red);
    cars.push_back(car_blue);
    cars.push_back(car_red);
    cars.push_back(car_blue);

    loaded = true;
    return 0;
}

sf::Texture* loader::get_texture(const std::string & name) {
    if (name == "map") {
        return &textures[0];
    } else if (name == "car_red") {
        return &textures[1];
    } else if (name == "car_blue") {
        return &textures[2];
    }
    return nullptr;
}

sf::Sprite* loader::get_car(size_t id) {
    return &cars[id];
}
