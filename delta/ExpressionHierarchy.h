//
// Created by Zakarie Aloui on 19/11/2023.
//

#ifndef DELTA_EXPRESSIONHIERARCHY_H
#define DELTA_EXPRESSIONHIERARCHY_H

#include <iostream>

typedef float Scalar;

class Sum;

class Product;


class ExpressionHierarchy {
protected:
    double value;
    double derivative;
public:
    ExpressionHierarchy();

    explicit ExpressionHierarchy(Scalar value);

    virtual void differentiate(Scalar h) = 0;

    Sum operator+(ExpressionHierarchy& other) const;

    Product operator*(ExpressionHierarchy& other) const;

    [[nodiscard]] Scalar getValue() const;

    [[nodiscard]] Scalar getDerivative() const;
};


class Variable : public ExpressionHierarchy {
public:
    Variable();

    explicit Variable(Scalar h);

    void differentiate(Scalar h) override;
};


class Sum : public ExpressionHierarchy {
public:
    Sum(const ExpressionHierarchy& lhs, ExpressionHierarchy& rhs);

    void differentiate(Scalar h) override;

private:
    ExpressionHierarchy& lhs;
    ExpressionHierarchy& rhs;
};

class Product : public ExpressionHierarchy {
public:
    Product(const ExpressionHierarchy& lhs, ExpressionHierarchy& rhs);

    void differentiate(Scalar h) override;

private:
    ExpressionHierarchy& lhs;
    ExpressionHierarchy& rhs;
};

class AffineTransformation : public ExpressionHierarchy {
public:
    AffineTransformation(Scalar a, ExpressionHierarchy& arg, Scalar b);

    AffineTransformation(Scalar a, ExpressionHierarchy& arg);

    void differentiate(Scalar h) override;

private:
    ExpressionHierarchy& arg;
    Scalar a, b;
};

std::ostream& operator<<(std::ostream& os, const ExpressionHierarchy& str);

inline const ExpressionHierarchy& conj(const ExpressionHierarchy& x) { return x; }

inline const ExpressionHierarchy& real(const ExpressionHierarchy& x) { return x; }

inline Variable imag(const ExpressionHierarchy&) { return Variable(0.); }

inline AffineTransformation abs(ExpressionHierarchy& x) {
    if (x.getValue() > 0) {
        return AffineTransformation(1, x);
    }
    return AffineTransformation(-1, x);
}

inline Product abs2(ExpressionHierarchy& x) { return x * x; }

#endif //DELTA_EXPRESSIONHIERARCHY_H
