#include "command.hpp"

move_command::move_command()
    : forward{false}
    , back{false}
    , right_turn{false}
    , left_turn{false}
    , run_sprint{false}
    , throw_side_object{false}
{}

move_command::move_command(const json& j) 
    : forward{j["forward"]}
    , back{j["back"]}
    , right_turn{j["right_turn"]}
    , left_turn{j["left_turn"]}
    , run_sprint{j["run_sprint"]}
    , throw_side_object{j["throw_side_object"]}
{}

json move_command::get_json() {
    return  {{"forward", forward}, {"back", back},
             {"right_turn", right_turn}, {"left_turn", left_turn},
             {"run_sprint", run_sprint}, {"throw_side_object", throw_side_object}};
}
