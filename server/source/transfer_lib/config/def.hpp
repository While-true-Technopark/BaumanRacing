#ifndef DEF_H_
#define DEF_H_

#include <iostream>
#include <nlohmann/json.hpp>
#include "config.hpp"

using json = nlohmann::json;
using point = std::array<double, DIM>;
using players_coord = std::array<point, MAX_USERS>;
using players_rating = std::array<size_t, MAX_USERS>;

#endif  // DEF_H_
