#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp> // или лучше std::vector?
#include <boost/numeric/ublas/io.hpp>
#include <function>

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

class map final {
 public:
	void make_move(const commad& comm, size_t player_id);
	std::vector<point> get_players_coord();
    std::vector<point> get_side_objects_coord();
    std::vector<size_t> get_rating();
    std::vector<bool> player_finished();
 private:
 	void on_pitstop(size_t player_id)
    std::vector<player> players;
    std::vector<side_object> side_objects;
    std::vector<point> road_coord;
    std::vector<point> pitstop_coords;
};

class solver final {
 public:
	solver() = default;
	~solver() {};

	solver(const solver&) = delete;
	solver& operator=(const solver&) = delete;

	solver(solver&&) = delete;
	solver& operator=(solver&&) = delete;

	static vector<double> linear(const matrix<double>& matrix, const std::string& method);
	static vector<double> nonlinear(const vector<std::function<double(vector<double>)>>& sistem, 
		                            const std::string& method);
	static vector<double> differential_equation(const vector<std::function<double(vector<double>)>>& rhs, 
		                                const vector<double>& init_cond, const std::string& method);

 private:
    vector<double> gauss(const matrix<double>& matrix);
    vector<double> qr(const matrix<double>& matrix);

    vector<double> newton(const vector<std::function<double(vector<double>)>>& sistem);
    vector<double> zeidel(const vector<std::function<double(vector<double>)>>& sistem);

    vector<double> runge_kutta(const vector<std::function<double(vector<double>)>>& rhs, 
    	                        const vector<double>& init_cond);
    vector<double> adams(const vector<std::function<double(vector<double>)>>& rhs, const vector<double>& init_cond);
};
