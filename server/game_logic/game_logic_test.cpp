#include "game_logic.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#define EPS 1e-5

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;
using testing::_;

bool operator==(const vector<double>& l, const vector<double>& r) {
    if (l.size() != r.size()) {
        return false;
    }
    for (size_t i = 0; i < l.size(); i++) {
        if (fabs(l(i) - r(i)) > EPS) {
            return false;
        }
    }
    return true;
}

class solve {
 public:
    solve() = default;
    virtual ~solve() {};
    virtual 
    vector<double> linear(const matrix<double>& matrix, const vector<double>& rhs) {
        return solver::gauss(matrix, rhs);
    }
    /*virtual vector<double> nonlinear(const vector<std::function<double(vector<double>)>>& sistem, 
        const std::string& method) {
        return solver::nonlinear(sistem, method);
    }

    virtual vector<double> differential_equation(const vector<std::function<double(vector<double>)>>& rhs, 
                                                const vector<double>& init_cond, const std::string& method) {
        return solver::differential_equation(rhs, init_cond, method);
    }*/
};

class mock_solve : public solve {
 public:
    mock_solve() : solve() {};
    MOCK_METHOD2(linear, vector<double>(const matrix<double>&, const vector<double>&));
    /*MOCK_METHOD2(nonlinear, vector<double>(const vector<std::function<double(vector<double>)>>&, const std::string&));
    MOCK_METHOD3(differential_equation, vector<double>(const vector<std::function<double(vector<double>)>>&, 
                                            const vector<double>&, const std::string&));*/
};

TEST(solver, linear) {
    mock_solve sol;
    size_t rows = 0, cols = 0;
    std::ifstream f("tests/1.txt");
    f >> rows >> cols;
    matrix<double> matr(rows, cols);
    vector<double> x(rows);
    vector<double> rhs(rows);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            f >> matr(i, j);
        }
        f >> x(i) >> rhs(i);
    }
    EXPECT_CALL(sol, linear(_, _)).WillOnce(Return(x));
    sol.linear(matr, rhs);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
