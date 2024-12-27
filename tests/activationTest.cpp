//
// Created by Zakarie Aloui on 26/11/2023.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include <Eigen/Dense>
#include "Expression.h"
#include "Activation.h"

using Delta::Expression;
using Eigen::Matrix;


TEST_CASE("ReLU of matrices", "[ReLU]") {
    Matrix<Expression, 3, 3> A, B, C, D, E, F, G;
    A << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    B << 1, -2, 3, -4, 0, -6, 7, -8, -9;
    C << 0, -1e-5, 1e-5, 2.4, -2.4, 6, -6, -0.1, 0.1;
    D << 1, 0, 3, 0, 0, 0, 7, 0, 0;
    E << 0, 0, 1e-5, 2.4, 0, 6, 0, 0, 0.1;
    F << 0, 0, 0, -1, -2, -3, -4, 0, -1;

    REQUIRE((Delta::ReLU<3, 3>(A) - A).squaredNorm() < 1e-10);
    REQUIRE((Delta::ReLU<3, 3>(B) - D).squaredNorm() < 1e-10);
    REQUIRE((Delta::ReLU<3, 3>(C) - E).squaredNorm() < 1e-10);
    REQUIRE((Delta::ReLU<3, 3>(F) - G).squaredNorm() < 1e-10);
}
