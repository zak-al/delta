//
// Created by Zakarie Aloui on 02/12/2023.
//

#ifndef DELTA_DOTPRODUCTSELFATTENTION_H
#define DELTA_DOTPRODUCTSELFATTENTION_H

#include <Eigen/Dense>
#include "Expression.h"

using Eigen::Matrix;
using Eigen::Vector;
using Eigen::Dynamic;
using Delta::Expression;

namespace Neurons {
    template<int EmbeddingDimension>
    class DotProductSelfAttention {
        Matrix<Expression, EmbeddingDimension, EmbeddingDimension> Wv, Wq, Wk; // Weights
        Vector<Expression, EmbeddingDimension> Bv, Bq, Bk; // Biases

        Matrix<Expression, Dynamic, Dynamic> infer(Matrix<Expression, EmbeddingDimension, Dynamic> input) {
            int N;
        }
    };
}

#endif //DELTA_DOTPRODUCTSELFATTENTION_H
