//
// Created by Zakarie Aloui on 26/11/2023.
//

#include "Activation.h"

Expression Delta::scalarReLU(const Expression& x)  {
    if (x > 0) {
        return x;
    }
    return 0;
}
