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

bool operator==(const std::vector<double>& l, const std::vector<double>& r) {
    if (l.size() != r.size()) {
        return false;
    }
    for (size_t i = 0; i < l.size(); i++) {
        if (fabs(l[i] - r[i]) > EPS) {
            return false;
        }
    }
    return true;
}

bool operator==(const matrix<double>& l, const matrix<double>& r) {
    if (l.size1() != r.size1() || l.size2() != r.size2()) {
        return false;
    }
    for (size_t i = 0; i < l.size1(); i++) {
    	for (size_t j = 0; j < l.size2(); j++) {
            if (fabs(l(i, j) - r(i, j)) > EPS) {
                return false;
            }
        }
    }
    return true;
}

class test_solver {
 public:
    test_solver() = default;
    virtual ~test_solver() {};
    virtual 
    std::vector<double> linear(const matrix<double>& matrix, const std::vector<double>& rhs) {
        return solver::gauss(matrix, rhs);
    }
    virtual 
    std::vector<double> nonlinear(const std::vector<std::function<double(const std::vector<double>&)>>& sistem) {
        return solver::newton(sistem);
    }
    virtual
    std::vector<double> differential_equation(const std::vector<std::function<double(const std::vector<double>&, double)>>& rhs, 
                                const std::vector<double>& init_cond, double dt) {
        return solver::runge_kutta(rhs, init_cond, dt);
    }
};

class mock_solver : public test_solver {
 public:
    MOCK_METHOD3(differential_equation, 
        std::vector<double>(const std::vector<std::function<double(const std::vector<double>&, double)>>&, 
                                const std::vector<double>&, double));
    MOCK_METHOD2(linear, std::vector<double>(const matrix<double>&, const std::vector<double>&));
    MOCK_METHOD1(nonlinear, std::vector<double>(const std::vector<std::function<double(const std::vector<double>&)>>&));
};

TEST(solver, linear) {
    mock_solver sol;
    size_t rows = 0, cols = 0;
    std::ifstream f("tests/1.txt");
    f >> rows >> cols;
    matrix<double> matr(rows, cols);
    std::vector<double> x(rows);
    std::vector<double> rhs(rows);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            f >> matr(i, j);
        }
        f >> x[i] >> rhs[i];
    }
    EXPECT_CALL(sol, linear(_, rhs)).WillOnce(Return(x));
    sol.linear(matr, rhs);
}

TEST(solver, nonlinear) {
    mock_solver sol;
    std::vector<std::function<double(const std::vector<double>&)>> sistem = {
        [](const std::vector<double>& x) {
            return x[0] * x[0] - x[1] * x[1] - 15;
        },
        [](const std::vector<double>& x) {
            return x[0] * x[1] + 4;
        }
    };
    std::vector<double> res = {4, -1};
    EXPECT_CALL(sol, nonlinear(_)).WillOnce(Return(res));
    sol.nonlinear(sistem);
}

TEST(solver, differential_equation) {
    mock_solver sol;
    std::vector<std::function<double(const std::vector<double>&, double)>> rhs = {
        [](const std::vector<double>& u, double t) { // уравнение колебаний в нормальной форме
        t++; // for -Werror=unused...
            return u[1];
        },
        [](const std::vector<double>& u, double t) {
            t++;
            return -t * u[0];
        }
    };
    std::vector<double> init_cond = {0, 0};
    double dt = 0.1;
    std::vector<double> res = {0, 0};
    EXPECT_CALL(sol, differential_equation(_, init_cond, dt)).WillOnce(Return(res));
    sol.differential_equation(rhs, init_cond, dt);
}

class mock_map : public map {
 public:
    MOCK_METHOD1(on_pitstop, bool(size_t));
};

TEST(map, on_pitstop) {
    mock_map m;
    EXPECT_CALL(m, on_pitstop(0)).WillOnce(Return(true));
    m.make_move({true, false, true, false, true, true}, 0);
    EXPECT_CALL(m, on_pitstop(1)).WillOnce(Return(false));
    m.throw_side_object(1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
