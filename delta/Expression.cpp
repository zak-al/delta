//
// Created by Zakarie Aloui on 16/11/2023.
//

#include "Expression.h"
#include "DomainError.h"
#include <format>

using namespace Delta;

std::string Delta::writeType(Type type) {
    switch (type) {
        case Sum:
            return "Sum";
        case Product:
            return "Product";
        case NaturalLog:
            return "NaturalLog";
        case Variable:
            return "Variable";
    }
}

Expression::Expression(Delta::Scalar value) {
    this->derivative = std::make_shared<Scalar>(0.0);
    this->type = Variable;
    this->value = value;
}


Expression::Expression(double value) : Expression(Scalar(value)) {}

Expression::Expression(const Expression& lhs, const Expression& rhs, Type type) {
    this->derivative = std::make_shared<Scalar>(0.0);
    this->type = type;
    this->lhs = std::make_shared<Expression>(lhs);
    this->rhs = std::make_shared<Expression>(rhs);

    switch (type) {
        case Sum:
            this->value = lhs.value + rhs.value;
            break;
        case Product:
            this->value = lhs.value * rhs.value;
            break;
        default:
            throw Delta::DomainError(std::format("Got two sub-expressions, "
                                                 "which is incompatible with type {}.", writeType(type)));
    }
}

Expression::Expression(const Expression& arg, Type type) {
    this->derivative = std::make_shared<Scalar>(0.0);
    this->type = type;
    this->lhs = std::make_shared<Expression>(arg);

    switch (type) {
        case NaturalLog:
            if (arg.getValue().imag() != 0) {
                throw Delta::DomainError(std::format("Cannot evaluate logarithm of argument {}, "
                                                     "which evaluates to non-real complex number {} + ({})i.",
                                                     arg.toString(),
                                                     arg.getValue().real(), arg.getValue().imag()));
            }
            if (arg.getValue().real() <= 0) {
                throw Delta::DomainError(std::format("Cannot evaluate logarithm of argument {}, "
                                                     "as it evaluates to {} which is not greater than 0.",
                                                     arg.toString(),
                                                     arg.getValue().real()));
            }
            this->value = log(arg.getValue().real());
            break;
        default:
            throw Delta::DomainError(std::format("Got a single sub-expression, "
                                                 "which is incompatible with type {}.", writeType(type)));
    }
}

Expression::Expression() : Expression(0.0) {}

Expression Expression::operator+(const Expression& other) const {
    return {*this, other, Sum};
}

Expression Expression::operator*(const Expression& other) const {
    return {*this, other, Product};
}

Expression Expression::operator*(Scalar scalar) const {
    return {scalar, *this, Product};
}

Expression Expression::operator*(double scalar) const {
    return {scalar, *this, Product};
}

Expression Expression::operator-() const {
    return {-1, *this, Product};
}

Expression Expression::operator-(const Expression& other) const {
    return {*this, -other, Sum};
}

bool Expression::operator<(const Expression& other) const {
    if (this->value.imag() != 0 || other.value.imag() != 0) {
        return false;
    }
    return this->getValue().real() < other.getValue().real();
}

bool Expression::operator<(double x) const {
    if (this->value.imag() != 0) {
        return false;
    }
    return this->getValue().real() < x;
}

bool Expression::operator>(const Expression& other) const {
    if (this->value.imag() != 0 || other.value.imag() != 0) {
        return false;
    }
    return this->getValue().real() > other.getValue().real();
}

bool Expression::operator>(double x) const {
    if (this->value.imag() != 0) {
        return false;
    }
    return this->getValue().real() > x;
}

bool Expression::operator==(const Expression& other) const {
    return this->getValue() == other.getValue();
}

bool Expression::operator!=(const Expression& other) const {
    return this->getValue() == other.getValue();
}

std::string Expression::toString() const {
    // todo parenthetise
    switch (this->type) {
        case Sum:
            return std::format("{} + {}", this->lhs->toString(), this->rhs->toString());
        case Product:
            return std::format("({}) * ({})", this->lhs->toString(), this->rhs->toString());
        case NaturalLog:
            return std::format("ln({})", this->lhs->toString());
        case Variable:
            if (this->getValue().imag() == 0) {
                return std::format("{}", this->getValue().real());
            }
            if (this->getValue().real() == 0) {
                return std::format("({})i", this->getValue().imag());
            }
            return std::format("{} + ({})i", this->getValue().real(), this->getValue().imag());
    }
}

Scalar Expression::getValue() const {
    return this->value;
}

Scalar Expression::getDerivative() const {
    return *(this->derivative);
}

void Expression::differentiate(Scalar h) const {
    *(this->derivative) += h;
    switch (type) {
        case Sum:
            this->lhs->differentiate(h);
            this->rhs->differentiate(h);
            break;
        case Product:
            this->lhs->differentiate(h * rhs->value);
            this->rhs->differentiate(h * lhs->value);
            break;
        case NaturalLog:
            this->lhs->differentiate(h / lhs->value);
        case Variable:
            break;
    }
}

void Expression::resetDerivative() const {
    *(this->derivative) = 0;
}

Expression operator*(double scalar, const Expression& expression) {
    return expression * scalar;
}

Expression log(const Expression& expression) {
    return Expression(expression, NaturalLog);
}

inline const Expression& conj(const Expression& x) { return x; }

inline const Expression& real(const Expression& x) { return x; }

inline Expression imag(const Expression&) { return 0.; }

//inline Expression abs(const Expression&  x)  { return fabs(x.getValue()); }
inline Expression abs2(const Expression& x) { return x * x; }

/*Delta::Scalar getValue(const Expression& e) {
    return e.getValue();
}

bool operator==(const Matrix<Expression, Dynamic, Dynamic>& x, const Matrix<Expression, Dynamic, Dynamic>& y) {
    return x.unaryExpr(&getValue) == y.unaryExpr(&getValue);
}*/
