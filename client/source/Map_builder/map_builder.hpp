#ifndef MAP_BUILDER_H_
#define MAP_BUILDER_H_

#include "base_builder.hpp"

class map_builder : public base_builder {
 public:
    void generate_map();
    sf::Sprite get_tile(const int row, const int col);
 private:
    std::vector<std::vector<int>> tile_matrix;
};

#endif  // MAP_BUILDER_H_
