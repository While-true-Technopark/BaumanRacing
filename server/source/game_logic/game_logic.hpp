#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <functional>

struct side_object {
    point coord;
    size_t ttl;
    double weight;
    double width;
    double height;
};

struct car {
    side_object equipment;
    double weight;
    double width;
    double height;
    double handleability;
    double max_speed;
    double max_acceleration;
};

struct player {
    size_t player_id;
    car player_car;
    point coord;
    point speed;
    point acceleration;
    point direction;
    bool on_pitstop;
};

class map {
 public:
    map() = default;
    virtual ~map() {}
    std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();
    std::vector<size_t> get_rating();
    bool player_finished(size_t player_id);
    void make_move(const command& comm, size_t player_id) {
        if (comm.forward) {
            std::cout << "comm.forward\n";
        }
        on_pitstop(player_id);
    }
    void throw_side_object(size_t player_id) {
        on_pitstop(player_id);
    }

 private:
    std::vector<player> players;
    std::vector<side_object> side_objects;
    std::vector<point> road_coord;
    std::vector<point> pitstop_coords;
    virtual bool on_pitstop(size_t player_id) {
        if (!player_id) {
            return true;
        }
        return false;
    }
};

class standard_maps final {
 public:
    static map get_map(size_t map_id) {
        if (map_id) {  // TODO(Рома): сделать набор стандартных карт
            return map();
        }
        return map();
    }
};

#endif  // GAME_LOGIC_H_
