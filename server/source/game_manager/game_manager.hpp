#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

//#include "game_logic.hpp"
#include "map.hpp"
#include "tinyxml2.h"


class game_manager {
 public:
    game_manager();
 private:
    game_map map;
}

/*int game_manager::create_map() { //TODO: path
    tinyxml2::XMLDocument doc;
    char[] path = "../client/static/";
    if (doc.LoadFile(path + "map.tmx")) {
        std::cout << "not found" << std::endl;
        return -1;
    }
    tinyxml2::XMLElement * map_xml = doc.FirstChildElement("map");
    if (map_xml == nullptr) {
        return -1;
    }
    size_t map_width = map_xml->IntAttribute("width", 0);
    size_t map_height = map_xml->IntAttribute("height", 0);
    size_t block_width = map_xml->IntAttribute("tilewidth", 0);
    size_t block_height = map_xml->IntAttribute("tileheight", 0);

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")
                                   ->FirstChildElement("data")
                                   ->FirstChildElement("tile"); // нужен ли delete?
    size_t i = 0;
    size_t j = 0;
    std::vector<map_block> block_stripes(map_width);
    do {
        map_block::block_type gid = tile_xml->IntAttribute("gid", 1);
        if (i == map_width) {
            map.push_back(block_stripes);
            i = 0;
            j++;
        }
        double x = i * block_width;
        double y = j * block_height;
        map_block block;
        //block.id = j * map_width + i;
         //block.type = gid;
        //if (gid == 1) {
        //    block.type = road;
        //} else if (gid == 2) {
         //   block.type = wall;
        //} else if (gid == 3) {
         //   block.type = 
        //}
        // block.passable = (gid == 2) ? false : true;   //  second block is unpassable
        block_stripes[i] = block;
        block_stripes[i][0] = x;
        block_stripes[i][1] = y;
        ++i;
    } while ((tile_xml = tile_xml->NextSiblingElement("tile")));

    return 0;
}*/

/*class game_manager {
 public:
    enum {players_coord, side_objects_coord, all_coord};
    explicit game_manager(const map& _map) : game_map(_map) {}
    virtual ~game_manager() {}
    void game_builder(const command& comm, size_t player_id) {
        if (comm.forward || comm.back || comm.right_turn
            || comm.left_turn || comm.run_sprint) {
            make_move(comm, player_id);
        }
        if (comm.throw_side_object) {
            throw_side_object(player_id);
        }
    }
    std::vector<point> get_coord(size_t whose_coord = all_coord) {
        switch (whose_coord) {
            case players_coord: {
                return get_players_coord();
            }
            case side_objects_coord: {
                return get_side_objects_coord();
            }
            default: {
                std::vector<point> coord = get_players_coord();
                std::vector<point> tmp = get_side_objects_coord();
                coord.insert(coord.end(), tmp.begin(), tmp.end());
                return coord;
            }
        }
    }

 private:
    map game_map;
    virtual void make_move(const command& comm, size_t player_id) = 0;
    virtual void throw_side_object(size_t player_id) = 0;
    virtual std::vector<point> get_players_coord() = 0;
    virtual std::vector<point> get_side_objects_coord() = 0;
};*/

#endif  // GAME_MANAGER_H_
