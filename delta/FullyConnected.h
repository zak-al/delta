//
// Created by Zakarie Aloui on 24/11/2023.
//

#ifndef DELTA_FULLYCONNECTED_H
#define DELTA_FULLYCONNECTED_H

#include <Eigen/Dense>
#include "Expression.h"
#include "deltaUtils.h"

using Delta::Expression;

namespace Neurons {
    template<int InputShape, int OutputShape>
    class FullyConnected {
    private:
        typedef Eigen::Matrix<Expression, InputShape, Eigen::Dynamic> InputType;
        typedef Eigen::Matrix<Expression, OutputShape, Eigen::Dynamic> OutputType;

        Eigen::Matrix<Expression, OutputShape, InputShape> W;
        Eigen::Vector<Expression, OutputShape> B;

        OutputType (* activationFunction)(OutputType);

    public:
        explicit FullyConnected(OutputType (* activationFunction)(OutputType)) {
            W = W.unaryExpr(&Delta::getRandomDouble);
            B = B.unaryExpr(&Delta::getRandomDouble);
            this->activationFunction = activationFunction;
        }

        OutputType infer(InputType input) {
            OutputType WX = W * input;
            return activationFunction(WX.colwise() + B);
        }
        
        Eigen::Matrix<Expression, OutputShape, InputShape> getWeights() const {
            return this->W;
        }

        Eigen::Vector<Expression, OutputShape> getBias() const {
            return this->B;
        }
    };
}

#endif //DELTA_FULLYCONNECTED_H
