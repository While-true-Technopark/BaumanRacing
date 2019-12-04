#include "game_manager.hpp"

game_manager::game_manager() 
    : run{false}
{}

void game_manager::start() {
    wait_before_start.restart();
    run = true;
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
    return !(map.get_num_circle(id) < NUM_CIRCLE);
}

bool game_manager::finish() {
    if (!run) {
        return true;
    }
    for (size_t idx = 0; idx < MAX_USERS; ++idx) {
        if (!finished(idx)) {
            return false;
        }
    }
    run = false;
    return true;
}

bool game_manager::update() {
    if (!run && wait_before_start.getElapsedTime() < TIME_OUT_BEFORE_START && finish()) {
        return false;
    }
    map.make_move();
    return true;
}

void game_manager::set_setting(size_t id, car_type type) {
    map.set_car(id, type);
}

void game_manager::set_setting(size_t id, const move_command& comm) {
    map.set_command(id, comm);
}


    



