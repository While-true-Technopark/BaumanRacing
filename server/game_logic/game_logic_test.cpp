#include "game_logic.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class solve {
 public:
 	virtual ~solve() {};
 	virtual vector<double> linear(const matrix<double>& matrix, const vector<double>& rhs, const std::string& method) {
 		return solver::linear(matrix, rhs, method);
 	}
 	virtual vector<double> nonlinear(const vector<std::function<double(vector<double>)>>& sistem, 
        const std::string& method) {
 		return solver::nonlinear(sistem, method);
 	}

 	virtual vector<double> differential_equation(const vector<std::function<double(vector<double>)>>& rhs, 
                                                const vector<double>& init_cond, const std::string& method) {
 		return solver::differential_equation(rhs, init_cond, method);
 	}
};

class mock_solve : public solve {
 public:
 	mock_solve() : solve() {};
 	MOCK_METHOD3(linear, vector<double>(const matrix<double>&, const vector<double>&, const std::string&));
 	MOCK_METHOD2(nonlinear, vector<double>(const vector<std::function<double(vector<double>)>>&, const std::string&));
 	MOCK_METHOD3(differential_equation, vector<double>(const vector<std::function<double(vector<double>)>>&, 
                                            const vector<double>&, const std::string&));
};

TEST(solver, game_builder) {
	mock_solve sol;
	matrix<double> m{{10, 6 , 2, 0}, {5, 1, -2, 4}, {3, 5, 1, -1}, {0, 6, -2, 2}};

}



int main(int argc, char** argv) {
  // ::testing::InitGoogleMock(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
