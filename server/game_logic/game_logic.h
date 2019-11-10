#ifndef PROJECT_GAME_LOGIC_H_
#define PROJECT_GAME_LOGIC_H_

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp> // или лучше std::vector?
#include <boost/numeric/ublas/io.hpp>
#include <functional>

using namespace boost::numeric::ublas;

struct point {
    double x;
    double y;
    double norm();
};

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

struct command {
    bool forward;
    bool back;
    bool right_turn;
    bool left_turn;
    bool throw_side_object;
    bool run_sprint;
};

class map final {
 public:
    void make_move(const command& comm, size_t player_id);
    std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();
    std::vector<size_t> get_rating();
    std::vector<bool> player_finished();
 private:
    void on_pitstop(size_t player_id);
    std::vector<player> players;
    std::vector<side_object> side_objects;
    std::vector<point> road_coord;
    std::vector<point> pitstop_coords;
};

class standard_maps final {
 public:
    static map get_map(size_t map_id) { 
        if (map_id) {  // TODO:
            return map();
        }
        return map();
    }
};

class solver final {
 public:
    solver() = default;
    ~solver() {};

    solver(const solver&) = delete;
    solver& operator=(const solver&) = delete;

    solver(solver&&) = delete;
    solver& operator=(solver&&) = delete;

    static vector<double> linear(const matrix<double>& matrix, const vector<double>& rhs, const std::string& method);
    static vector<double> nonlinear(const vector<std::function<double(vector<double>)>>& sistem, 
                                        const std::string& method);
    static vector<double> differential_equation(const vector<std::function<double(vector<double>)>>& rhs, 
                                                const vector<double>& init_cond, const std::string& method);

 private:
    vector<double> gauss(const matrix<double>& matrix, const vector<double>& rhs);
    vector<double> qr(const matrix<double>& matrix, const vector<double>& rhs);

    vector<double> newton(const vector<std::function<double(vector<double>)>>& sistem);
    vector<double> zeidel(const vector<std::function<double(vector<double>)>>& sistem);

    vector<double> runge_kutta(const vector<std::function<double(vector<double>)>>& rhs, 
                                const vector<double>& init_cond);
    vector<double> adams(const vector<std::function<double(vector<double>)>>& rhs, const vector<double>& init_cond);
};

#endif  // PROJECT_GAME_LOGIC_H_
