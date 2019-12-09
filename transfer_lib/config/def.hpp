#ifndef DEF_H_
#define DEF_H_

#include <iostream>
#include <nlohmann/json.hpp>
#include "config.hpp"

using json = nlohmann::json;
using point = std::array<double, DIM>;
using position = std::array<double, DOF>;
using players_position = std::array<position, MAX_USERS>;
using players_rating = std::array<size_t, MAX_USERS>;

#endif  // DEF_H_
