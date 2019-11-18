#include "renderer.hpp"

renderer::renderer(sf::RenderWindow *win) {
    window = win;
    paths_to_xml_maps.push_back("static/map.tmx");
    scale = 0.12;
}

int renderer::create_map(size_t map_number, sf::Texture* map_texture) {
    using namespace tinyxml2;
    using namespace sf;
    XMLDocument doc;
    if (doc.LoadFile(paths_to_xml_maps[map_number].c_str())) {
        return -1;
    }
    XMLElement * map_xml = doc.FirstChildElement("map");
    if (map_xml == nullptr) {
        return -1;
    }
    size_t map_width = map_xml->IntAttribute("width", 0);
    size_t map_height = map_xml->IntAttribute("height", 0);
    size_t block_width = map_xml->IntAttribute("tilewidth", 0);
    size_t block_height = map_xml->IntAttribute("tileheight", 0);

    std::string tileset_tsx = map_xml->FirstChildElement("tileset")->Attribute("source");
    XMLDocument doc_tileset;
    tileset_tsx = "static/" + tileset_tsx;
    if (doc_tileset.LoadFile(tileset_tsx.c_str())) {
        return -1;
    }
    XMLElement * tileset = doc_tileset.FirstChildElement("tileset");
    size_t sprite_width = tileset->IntAttribute("tilewidth", 0);
    size_t sprite_height = tileset->IntAttribute("tileheight", 0);
    size_t sprite_count = tileset->IntAttribute("tilecount", 0);
    size_t sprite_columns = tileset->IntAttribute("columns", 0);

    map_texture->setSmooth(true);
    std::vector<Sprite> block_sprites;
    size_t cur_x = 0;
    size_t cur_y = 0;
    for (size_t i = 0; i != sprite_count; i++) {
        if (!(i % sprite_columns) && i) {
            cur_y += sprite_height;
            cur_x = 0;
        }
        block_sprites.push_back(Sprite(*map_texture, IntRect(cur_x, cur_y, sprite_width, sprite_height)));
        cur_x += sprite_width;
    }

    // for (int i = 0; i != block_sprites.size(); i++) {
    //     window->draw(block_sprites[i]);
    // }
    // window->display();
    XMLElement * tile_xml = map_xml->FirstChildElement("layer")
                                   ->FirstChildElement("data")
                                   ->FirstChildElement("tile");
    size_t i = 0;
    size_t j = 0;
    std::vector<map_block> block_stripes(map_width);
    do {
        size_t gid = tile_xml->IntAttribute("gid", 1);
        if (i == map_width) {
            map.push_back(block_stripes);
            i = 0;
            j++;
        }
        float x = i * block_width;
        float y = j * block_height;
        map_block block;
        block.id = j * map_width + i;
        block.passable = (gid == 2) ? false : true;   //  second block is unpassable
        block.sprite = block_sprites[gid - 1];
        block.sprite.setPosition(sf::Vector2f(x * scale, y * scale));
        block.sprite.scale(sf::Vector2f(scale, scale));
        block_stripes[i] = block;
        i++;
    } while ((tile_xml = tile_xml->NextSiblingElement("tile")));

    return 0;
}

int renderer::build_game_scene(game_render_data data) {
    window->clear();
    for (size_t i = 0; i != map.size(); i++) {
        for (size_t j = 0; j != map[0].size(); j++) {
            window->draw(map[i][j].sprite);
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

