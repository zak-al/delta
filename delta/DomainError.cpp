//
// Created by Zakarie Aloui on 02/12/2023.
//

#include "DomainError.h"

using Delta::DomainError;

DomainError::DomainError(const std::string& description): std::exception() {
    this->description = "[DomainError] " + description;
}
