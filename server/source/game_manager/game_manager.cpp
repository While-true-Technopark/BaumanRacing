#include "game_manager.hpp"

game_manager::game_manager(size_t num_players) 
    : map(num_players)
    , start{false}
{}

void game_manager::run() {
    wait_before_start.restart();
    start = true;
    map.set_start_pos();
}

players_position game_manager::get_players_pos() const {
    return map.get_players_pos();
}

players_rating game_manager::get_rating() const {
    return map.get_rating();
}

std::vector<position> game_manager::get_side_objects_pos() const {
    return map.get_side_objects_pos();
}

bool game_manager::finished(size_t id) const {
    return !(map.get_num_circle(id) < NUM_CIRCLE); // map.get_num_circle(id) >= NUM_CIRCLE;
}

bool game_manager::finish() {
    for (size_t idx = 0; idx < MAX_USERS; ++idx) {
        if (!finished(idx)) {
            return false;
        }
    }
    start = false;
    return true;
}

void game_manager::update() {
    if (start && wait_before_start.getElapsedTime() > TIME_OUT_BEFORE_START && !finish()) {
        map.make_move();
    }
}

void game_manager::set_setting(size_t id, game_object_type type) {
    map.set_setting(id, type);
}

void game_manager::set_setting(size_t id, const move_command& comm) {
    map.set_setting(id, comm);
}
