#ifndef COMMAND_H_
#define COMMAND_H_

#include "def.hpp"

enum class car_type {
    small,
    medium,
    big,
};

class move_command {
 public:
    move_command();
    move_command(const json& j);
    json get_json();
    bool forward;
    bool back;
    bool right_turn;
    bool left_turn;
    bool run_sprint;
    bool throw_side_object;
};

#endif  // COMMAND_H_
