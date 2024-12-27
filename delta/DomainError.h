//
// Created by Zakarie Aloui on 02/12/2023.
//

#ifndef DELTA_DOMAINERROR_H
#define DELTA_DOMAINERROR_H

#include <exception>
#include <string>

namespace Delta {
    class DomainError : public std::exception {
    private:
        std::string description;
    public:
        explicit DomainError(const std::string& description);

        [[nodiscard]] const char* what() const noexcept override {
            return this->description.c_str();
        }
    };
}

#endif //DELTA_DOMAINERROR_H
