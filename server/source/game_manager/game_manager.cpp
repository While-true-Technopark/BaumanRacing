#include "game_manager.hpp"

const int8_t NUM_CIRCLE = 1;

game_manager::game_manager(size_t num_players) 
    : num_players{num_players}
    , map(num_players)
    , start{false}
    , num_finished{0}
{}

bool game_manager::load_map(/*передавать id карты*/) {
    return map.load("default_maps/map.tmx");
}

void game_manager::run() {
    wait_before_start.restart();
    start = true;
    map.start();
}

std::vector<game_object_type> game_manager::get_setting() const {
    return map.get_setting();
}

std::vector<position> game_manager::get_players_pos() const {
    return map.get_players_pos();
}

std::vector<size_t> game_manager::get_rating() const {
    return std::vector<size_t>();
}

std::vector<position> game_manager::get_side_objects_pos() const {
    return map.get_side_objects_pos();
}

size_t game_manager::finished(size_t id) {
    if (!(map.get_num_circle(id) < NUM_CIRCLE)) { // map.get_num_circle(id) >= NUM_CIRCLE;
        return ++num_finished;
    }
    return 0;
}

bool game_manager::finish() {
    for (size_t idx = 0; idx < num_players; ++idx) {
        if (!finished(idx)) {
            return false;
        }
        ++num_finished;
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
