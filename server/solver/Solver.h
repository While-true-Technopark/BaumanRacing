#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp> // или лучше std::vector?
#include <boost/numeric/ublas/io.hpp>
#include <function>

using namespace boost::numeric::ublas;

class solver final {
 public:
	solver() = default;
	~solver() {};

	solver(const solver&) = delete;
	solver& operator=(const solver&);

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
}