#ifndef GAME_BUILDER_H_
#define GAME_BUILDER_H_

#include "base_builder.hpp"
#include "game_render_data.hpp"
#include "map_builder.hpp"

class game_builder : public base_builder {
 public:
    void build_scene(game_render_data data);

 private:
    game_render_data data;
    map_builder map;

    void build_rating();
    void build_map();
    void build_car();
    void build_cars();
};

#endif  // GAME_BUILDER_H_
