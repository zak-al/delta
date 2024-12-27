//
// Created by Zakarie Aloui on 19/11/2023.
//

#ifndef DELTA_NUMTRAITS_H
#define DELTA_NUMTRAITS_H

#include <Eigen/Core>
#include "ExpressionHierarchy.h"
#include <float.h>

namespace Eigen {
    template<> struct NumTraits<ExpressionHierarchy>: NumTraits<double> {
        typedef Variable Real;
        typedef Variable NonInteger;
        typedef Variable Literal;
        typedef Variable Nested;

        static inline Real epsilon() { return Variable(1e-15); }
        static inline Real dummy_precision() { return Variable(1e-15); }
        static inline Real highest() { return Variable(DBL_MAX); }
        static inline Real lowest() { return Variable(DBL_MIN); }
        static inline int digits10() { return std::numeric_limits<double>::digits10; }
        static inline int digits() { return std::numeric_limits<double>::digits; }

        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };
}

#endif //DELTA_NUMTRAITS_H
