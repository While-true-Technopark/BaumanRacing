#include "renderer.hpp"
#include <chrono>
#include <thread>
#include <iostream>

renderer::renderer(sf::RenderWindow* win) {
    window = win;
    window_size = window->getSize();
    view = window->getView();
}

renderer::~renderer() {}

int renderer::init(init_data data) {
    if (data.main_font) {
        play_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 244),
            "Play"
        });
        settings_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 344),
            "Settings"
        });
        new_room_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 244),
            "Create new room"
        });
        connect_to_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 344),
            "Connect to existing room"
        });
        enter_new_name_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 244),
            "Enter name of new room"
        });
        enter_exists_name_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 244),
            "Enter name of existing room"
        });
        waiting_text = build_text({
            sf::Color::White,
            data.main_font,
            "topleft",
            sf::Vector2f(window_size.x / 2, 344),
            ""
        });
        input_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 344),
            ""
        });
        digit_text = build_text({
            sf::Color::Yellow,
            data.main_font,
            "center",
            sf::Vector2f(0, 0),
            "3"
        });

        finish_pos_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 244),
            "Your position is "
        });
        press_enter_text = build_text({
            sf::Color::White,
            data.main_font,
            "center",
            sf::Vector2f(window_size.x / 2, 344),
            "Press enter to continue..."
        });
    }

    if (data.cars_textures.size()) {
        for (size_t i = 0; i != data.cars_textures.size(); i++) { // TODO gavroman: Сделать загрузку тесктур в спрайты согласно данным с сервера
            sf::Sprite car(*data.cars_textures[i]);
            car.setOrigin(data.cars_textures[i]->getSize().x / 2, data.cars_textures[i]->getSize().y / 2);
            players.push_back(car);
        }
        for (size_t i = 0; i != data.cars_textures.size(); i++) {
            cars_choose.push_back(build_sprite({
                data.cars_textures[i],
                true,
                sf::Vector2f(window_size.x / 2, window_size.y / 2),
                90.f,
                sf::Vector2f(2.f, 2.f)
            }));
        }
    }

    if (data.map_texture) {
        map = build_sprite({
           data.map_texture,
           false,
           sf::Vector2f(0, 0),
           0.f,
           sf::Vector2f(1, 1)
        });
    }
    if (data.logo_texture) {
        logo = build_sprite({
            data.logo_texture,
            true,
            sf::Vector2f(window_size.x / 2, 50),
            0.f,
            sf::Vector2f(1, 1)
        });
    }
    if (data.arrow_texture) {
        arrow_l = build_sprite({
            data.arrow_texture,
            true,
            sf::Vector2f(140, window_size.y / 2),
            0.f,
            sf::Vector2f(1, 1)
        });
    }
    if (data.arrow_texture) {
        arrow_r = build_sprite({
            data.arrow_texture,
            true,
            sf::Vector2f(window_size.x - 140, window_size.y / 2),
            180.f,
            sf::Vector2f(1, 1)
        });
    }
    if (data.box_texture) {
        box = build_sprite({
            data.box_texture,
            true,
            sf::Vector2f(0, 0),
            0.f,
            sf::Vector2f(1, 1)
        });
    }

    return RNDR_OK;
}

int renderer::build_start_scene(game_render_data data) {
    view.setCenter(sf::Vector2f(data.players[0].position.x, data.players[0].position.y));
    digit_text.setCharacterSize(250);
    sf::FloatRect text_bounds = digit_text.getLocalBounds();
    digit_text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    digit_text.setPosition(view.getCenter().x, view.getCenter().y - 50);
    digit_text.setOutlineColor(sf::Color::Black);
    digit_text.setOutlineThickness(12);
    digit_text.setRotation(25);
    view.setRotation(25);
    window->setView(view);
    std::array<std::string, 3> timeout_text = {"3","2","1"};
    int wait_time = TIME_OUT_BEFORE_START.asMilliseconds() / timeout_text.size();
    for (size_t i = 0; i != timeout_text.size(); i++) {
        window->clear();
        window->draw(map);
        for (size_t j = 0; j != players.size(); j++) {
            players[j].setPosition(data.players[j].position.x, data.players[j].position.y);
            players[j].setRotation(data.players[j].position.angle);
            window->draw(players[j]);
        }
        digit_text.setString(timeout_text[i]);
        window->draw(digit_text);
        window->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
    return RNDR_OK;
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
    return RNDR_OK;
}

int renderer::car_choose_menu() {
    return RNDR_OK;
}

int renderer::lobby_scene() {
    return RNDR_OK;
}

int renderer::show_car(size_t index) {
    window->clear();
    window->draw(logo);
    window->draw(arrow_l);
    window->draw(arrow_r);
    window->draw(cars_choose[index]);
    window->display();
    return RNDR_OK;
}

int renderer::main_menu(size_t box_select) {
    window->clear();
    box.setPosition(window_size.x / 2, box_select * 100 + 250);

    window->draw(logo);
    window->draw(box);
    window->draw(play_text);
    window->draw(settings_text);
    window->display();
    return RNDR_OK;
}

int renderer::connect_to_open(size_t box_select) {
    window->clear();
    box.setPosition(window_size.x / 2, box_select * 100 + 250);

    window->draw(logo);
    window->draw(box);
    window->draw(new_room_text);
    window->draw(connect_to_text);
    window->display();
    return RNDR_OK;
}

int renderer::create_room(const char (*str)[256]) {
    window->clear();
    std::string s(*str);
    input_text.setString(s);
    sf::FloatRect bounds(input_text.getGlobalBounds());
    input_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

    window->draw(logo);
    window->draw(enter_new_name_text);
    window->draw(input_text);
    window->display();
    return RNDR_OK;
}

int renderer::show_wait(size_t waiting) {
    window->clear();
    if (waiting == 0) {
        waiting_text.setString("Waiting for players");
    } else {
        waiting_text.setString("player " + std::to_string(waiting) + " connected");
    }
    sf::FloatRect bounds(waiting_text.getGlobalBounds());
    waiting_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
    window->draw(logo);
    window->draw(waiting_text);
    window->display();
    return RNDR_OK;
}

int renderer::connect_to_room(const char (*str)[256]) {
    window->clear();
    std::string s(*str);
    input_text.setString(s);
    sf::FloatRect bounds(input_text.getGlobalBounds());
    input_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

    window->draw(logo);
    window->draw(enter_exists_name_text);
    window->draw(input_text);
    window->display();
    return RNDR_OK;
}

int renderer::end_game_menu(int position) {
    window->clear();
    window->draw(logo);
    view.setCenter(sf::Vector2f(window_size.x / 2, window_size.y /2));
    view.setRotation(0.f);
    window->setView(view);

    std::string text = finish_pos_text.getString();
    text += std::to_string(position);
    finish_pos_text.setString(text);

    window->draw(finish_pos_text);
    window->draw(press_enter_text);
    window->display();
    return RNDR_OK;
}

int renderer::settings_menu() {
    return RNDR_OK;
}

sf::Text renderer::build_text(const text_props props) {
    sf::Text return_text;
    return_text.setFont(*props.font);
    return_text.setString(props.string);
    if (props.centered) {
        sf::FloatRect bounds(return_text.getGlobalBounds());
        return_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
    } else {
        return_text.setOrigin(sf::Vector2f(0.f, 0.f));
    }
    return_text.setFillColor(props.fill_color);
    return_text.setPosition(props.position);
    return return_text;
}

sf::Sprite renderer::build_sprite(const sprite_props props) {
    sf::Sprite return_sprite;
    return_sprite.setTexture(*props.texture);
    if (props.centered) {
        sf::Vector2f texture_size(props.texture->getSize());
        return_sprite.setOrigin(texture_size.x / 2 , texture_size.y / 2);
    } else {
        return_sprite.setOrigin(sf::Vector2f(0.f, 0.f));
    }
    return_sprite.setPosition(props.position);
    return_sprite.setRotation(props.rotation);
    return_sprite.setScale(props.scale);
    return return_sprite;
}

