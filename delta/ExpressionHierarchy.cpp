//
// Created by Zakarie Aloui on 19/11/2023.
//

#include "ExpressionHierarchy.h"

ExpressionHierarchy::ExpressionHierarchy(Scalar value) {
    this->value = value;
    this->derivative = 0;
}

ExpressionHierarchy::ExpressionHierarchy() {
    this->value = 0;
    this->derivative = 0;
}

Scalar ExpressionHierarchy::getValue() const {
    return this->value;
}

Sum ExpressionHierarchy::operator+(ExpressionHierarchy& other) const {
    return {*this, other};
}

Product ExpressionHierarchy::operator*(ExpressionHierarchy& other) const {
    return {*this, other};
}

Scalar ExpressionHierarchy::getDerivative() const {
    return this->derivative;
}

void Sum::differentiate(Scalar h) {
    this->derivative += h;
    this->lhs.differentiate(h);
    this->rhs.differentiate(h);
}

Sum::Sum(const ExpressionHierarchy& lhs, ExpressionHierarchy& rhs) :
        ExpressionHierarchy(lhs.getValue() + rhs.getValue()), lhs(const_cast<ExpressionHierarchy&>(lhs)), rhs(rhs) {}

void Variable::differentiate(Scalar h) {
    this->derivative += h;
}

Variable::Variable(Scalar h) : ExpressionHierarchy(h) {}

Variable::Variable() : ExpressionHierarchy() {}

void Product::differentiate(Scalar h) {
    this->derivative += h;
    this->lhs.differentiate(h * this->rhs.getValue());
    this->rhs.differentiate(h * this->lhs.getValue());
}

Product::Product(const ExpressionHierarchy& lhs, ExpressionHierarchy& rhs) :
        ExpressionHierarchy(lhs.getValue() * rhs.getValue()), lhs(const_cast<ExpressionHierarchy&>(lhs)), rhs(rhs) {}

std::ostream& operator<<(std::ostream& os, const ExpressionHierarchy& str) {
    os << str.getValue();
    return os;
}

AffineTransformation::AffineTransformation(Scalar a, ExpressionHierarchy& arg, Scalar b) : ExpressionHierarchy(a * arg.getValue() + b), arg(arg) {
    this->a = a;
    this->b = b;
}

void AffineTransformation::differentiate(Scalar h) {
    arg.differentiate(a * h);
    this->derivative += h;
}

AffineTransformation::AffineTransformation(Scalar a, ExpressionHierarchy& arg): AffineTransformation(a, arg, 0) {}
