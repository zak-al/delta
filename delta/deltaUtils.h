//
// Created by Zakarie Aloui on 22/11/2023.
//

#ifndef DELTA_DELTAUTILS_H
#define DELTA_DELTAUTILS_H

#include "Expression.h"
#include <Eigen/Dense>
#include <random>

using Eigen::Matrix;
using Eigen::Dynamic;

namespace Delta {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normal_distribution(0., 1.);

    Delta::Scalar getGradient(Delta::Expression const& x);
    Delta::Expression getRandomDouble();
}

#endif //DELTA_DELTAUTILS_H
