#include "renderer.hpp"

renderer::renderer(sf::RenderWindow* win) {
    window = win;
    view = window->getView();
    view.zoom(1.0f);
}

int renderer::init(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture) {
    map_texture = map_texture;
    for (size_t i = 0; i != cars_textures.size(); i++) {
        sf::Sprite car(*cars_textures[i]);
        car.setOrigin(cars_textures[i]->getSize().x / 2, cars_textures[i]->getSize().y / 2);
        players.push_back(car);
    }
    map.setTexture(*map_texture);
    return 0;
}


int renderer::build_game_scene(game_render_data data) {
    window->clear();

    sf::Vector2f center(data.players[0].position.x, data.players[0].position.y);

    // {
    //     float width = window->getSize().x;
    //     float height = window->getSize().y;
    //     map.setTextureRect(sf::IntRect(center.x - width / 2, center.y - height / 2, width, height));
    //     window->draw(map);
    //     for (size_t i = 0; i != players.size(); i++) {
    //         players[i].setPosition(data.players[i].position.x - data.players[0].position.x + width / 2,
    //                                data.players[i].position.y - data.players[0].position.y + height / 2);
    //         players[i].setRotation(data.players[i].position.angle);
    //         window->draw(players[i]);
    //     }
    // }
    {
        view.setCenter(center);
        window->setView(view);
        window->draw(map);
        for (size_t i = 0; i != players.size(); i++) {
            players[i].setPosition(data.players[i].position.x, data.players[i].position.y);
            players[i].setRotation(data.players[i].position.angle);
            window->draw(players[i]);
        }
    }

    window->display();
    return 0;
}

int renderer::car_choose_menu() {
    return 0;
}

int renderer::end_game_menu() {
    return 0;
}

int renderer::lobby_scene() {
    return 0;
}

int renderer::main_menu() {
    return 0;
}

int renderer::settings_menu() {
    return 0;
}

int renderer::wait_scene() {
    return 0;
}

int renderer::build_map() {
    return 0;
}

int renderer::build_rating() {
    return 0;
}

int renderer::build_car() {
    return 0;
}

int renderer::build_cars() {
    return 0;
}

