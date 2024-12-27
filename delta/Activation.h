//
// Created by Zakarie Aloui on 26/11/2023.
//

#ifndef DELTA_ACTIVATION_H
#define DELTA_ACTIVATION_H

#include <Eigen/Dense>
#include "Expression.h"

using Delta::Expression;
using Eigen::Matrix;

namespace Delta {
    Expression scalarReLU(const Expression& x);

    template<int rows, int cols>
    Matrix <Expression, rows, cols> ReLU(const Matrix <Expression, rows, cols>& input) {
        return input.unaryExpr(&scalarReLU);
    }
}

#endif //DELTA_ACTIVATION_H
