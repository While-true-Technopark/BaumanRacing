#include "renderer.hpp"
#include <cmath>
#include <string>

renderer::renderer(sf::RenderWindow* win) {
    window = win;
    view = window->getView();
}

int renderer::init(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture,
                   sf::Texture* logo_texture, sf::Texture* box_texture,
                   sf::Texture* arrow_texture, sf::Font *main_font) {
    map_texture = map_texture;
    main_font = main_font;
    
    play_text.setFont(*main_font);
    play_text.setString("Play");
    play_text.setOrigin(sf::Vector2f(play_text.getGlobalBounds().width / 2,
                                     play_text.getGlobalBounds().height / 2));
    play_text.setFillColor(sf::Color::White);
    play_text.setPosition(window->getSize().x / 2, 244);
    
    settings_text.setFont(*main_font);
    settings_text.setString("Settings");
    settings_text.setOrigin(sf::Vector2f(settings_text.getGlobalBounds().width / 2,
                                         settings_text.getGlobalBounds().height / 2));
    settings_text.setFillColor(sf::Color::White);
    settings_text.setPosition(window->getSize().x / 2, 344);
    
    new_room_text.setFont(*main_font);
    new_room_text.setString("Create new room");
    new_room_text.setOrigin(sf::Vector2f(new_room_text.getGlobalBounds().width / 2,
                                         new_room_text.getGlobalBounds().height / 2));
    new_room_text.setFillColor(sf::Color::White);
    new_room_text.setPosition(window->getSize().x / 2, 244);
    
    connect_to_text.setFont(*main_font);
    connect_to_text.setString("Connect to exists room");
    connect_to_text.setOrigin(sf::Vector2f(connect_to_text.getGlobalBounds().width / 2,
                                           connect_to_text.getGlobalBounds().height / 2));
    connect_to_text.setFillColor(sf::Color::White);
    connect_to_text.setPosition(window->getSize().x / 2, 344);
    
    enter_new_name_text.setFont(*main_font);
    enter_new_name_text.setString("Enter name of new room");
    enter_new_name_text.setOrigin(sf::Vector2f(enter_new_name_text.getGlobalBounds().width / 2,
                                               enter_new_name_text.getGlobalBounds().height / 2));
    enter_new_name_text.setFillColor(sf::Color::White);
    enter_new_name_text.setPosition(window->getSize().x / 2, 244);
    
    enter_exists_name_text.setFont(*main_font);
    enter_exists_name_text.setString("Enter name of exists room");
    enter_exists_name_text.setOrigin(sf::Vector2f(enter_exists_name_text.getGlobalBounds().width / 2,
        enter_exists_name_text.getGlobalBounds().height / 2));
    enter_exists_name_text.setFillColor(sf::Color::White);
    enter_exists_name_text.setPosition(window->getSize().x / 2, 244);
    
    waiting_text.setFont(*main_font);
    waiting_text.setFillColor(sf::Color::White);
    waiting_text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
    
    input_text.setFont(*main_font);
    input_text.setString("");
    input_text.setOrigin(sf::Vector2f(input_text.getGlobalBounds().width / 2,
                                      input_text.getGlobalBounds().height / 2));
    input_text.setFillColor(sf::Color::White);
    input_text.setPosition(window->getSize().x / 2, 344);
    
    for (size_t i = 0; i != 3; i++) { // TODO gavroman: Сделать загрузку тесктур в спрайты согласно данным с сервера
        if (i < 3) {
            sf::Sprite car(*cars_textures[i]);
            car.setOrigin(cars_textures[i]->getSize().x / 2, cars_textures[i]->getSize().y / 2);
            players.push_back(car);
        } else {
            sf::Sprite car(*cars_textures[1]);
            car.setOrigin(cars_textures[1]->getSize().x / 2, cars_textures[1]->getSize().y / 2);
            players.push_back(car);
        }
    }
    
    for (size_t i = 0; i != cars_textures.size(); i++) {
        sf::Sprite car(*cars_textures[i]);
        car.setOrigin(cars_textures[i]->getSize().x / 2, cars_textures[i]->getSize().y / 2);
        car.setPosition(window->getSize().x/2, window->getSize().y/2);
        car.setRotation(90);
        car.scale(2.0f, 2.0f);
        cars_choose.push_back(car);
    }
    
    
    map.setTexture(*map_texture);
    
    logo.setTexture(*logo_texture);
    logo.setOrigin(logo.getTexture()->getSize().x/2, logo.getTexture()->getSize().y/2);
    logo.setPosition(window->getSize().x/2, 50);
    
    arrow_l.setTexture(*arrow_texture);
    arrow_l.setOrigin(arrow_l.getTexture()->getSize().x/2, arrow_l.getTexture()->getSize().y/2);
    arrow_l.setPosition(140, window->getSize().y/2);
    
    arrow_r.setTexture(*arrow_texture);
    arrow_r.setOrigin(arrow_r.getTexture()->getSize().x/2, arrow_r.getTexture()->getSize().y/2);
    arrow_r.setPosition(window->getSize().x - 140, window->getSize().y/2);
    arrow_r.setRotation(180);
    
    box.setTexture(*box_texture);
    box.setOrigin(box.getTexture()->getSize().x/2, box.getTexture()->getSize().y/2);
    return 0;
}

int renderer::build_game_scene(game_render_data data) {
    window->clear();
    view.setCenter(sf::Vector2f(data.players[0].position.x, data.players[0].position.y));
    window->setView(view);
    window->draw(map);
    for (size_t i = 0; i != players.size(); i++) {
        players[i].setPosition(data.players[i].position.x, data.players[i].position.y);
        players[i].setRotation(data.players[i].position.angle);
        window->draw(players[i]);
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

int renderer::show_car(size_t index) {
    window->clear();

    window->draw(logo);
    window->draw(arrow_l);
    window->draw(arrow_r);
    window->draw(cars_choose[index]);
    
    window->display();
    
    return 0;
}

int renderer::main_menu(size_t box_select) {
    window->clear();
    
    window->draw(logo);
    
    box.setPosition(window->getSize().x/2, box_select * 100 + 250);
    window->draw(box);
    
    window->draw(play_text);
    window->draw(settings_text);
    
    window->display();
    return 0;
}

int renderer::connect_to_open(size_t box_select) {
    window->clear();
    
    window->draw(logo);
    
    box.setPosition(window->getSize().x/2, box_select * 100 + 250);
    window->draw(box);
    
    window->draw(new_room_text);
    window->draw(connect_to_text);
    
    window->display();
    return 0;
}

int renderer::create_room(const char (*str)[256]) {
    window->clear();
    
    window->draw(logo);
    window->draw(enter_new_name_text);
    
    std::string s(*str);
    input_text.setString(s);
    input_text.setOrigin(sf::Vector2f(input_text.getGlobalBounds().width / 2,
                                      input_text.getGlobalBounds().height / 2));
    window->draw(input_text);
    
    window->display();
    return 0;
}

int renderer::show_wait(size_t waiting) {
    window->clear();
    if (waiting == 0) {
        waiting_text.setString("Waiting for players");
    } else {
        waiting_text.setString("player " + std::to_string(waiting) + " connected");
    }
    
    waiting_text.setOrigin(sf::Vector2f(waiting_text.getGlobalBounds().width / 2,
        waiting_text.getGlobalBounds().height / 2));
    
    window->draw(logo);
    window->draw(waiting_text);
    window->display();
    return 0;
}

int renderer::connect_to_room(const char (*str)[256]) {
    window->clear();

    window->draw(logo);
    window->draw(enter_exists_name_text);
    
    std::string s(*str);
    input_text.setString(s);
    input_text.setOrigin(sf::Vector2f(input_text.getGlobalBounds().width / 2,
                                      input_text.getGlobalBounds().height / 2));
    window->draw(input_text);
    
    window->display();
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

