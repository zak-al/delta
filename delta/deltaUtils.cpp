//
// Created by Zakarie Aloui on 22/11/2023.
//

#include "deltaUtils.h"
using Delta::Expression;

Delta::Scalar Delta::getGradient(const Expression& x) {
    return x.getDerivative();
}

Expression Delta::getRandomDouble() {
    return normal_distribution(gen);
}

