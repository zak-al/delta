//
// Created by Zakarie Aloui on 16/11/2023.
//

#ifndef DELTA_EXPRESSION_H
#define DELTA_EXPRESSION_H

#include <iostream>
#include <complex>

// todo domain error with logs
// todo linear combinations

namespace Delta {
    enum Type {
        Sum,
        Product,
        NaturalLog,
        Variable,
    };

    typedef std::complex<double> Scalar;

    std::string writeType(Type type);

    class Expression {
    private:
        Type type;
        Scalar value;
        std::shared_ptr<Scalar> derivative;
        std::shared_ptr<Expression> lhs, rhs;

    public:
        Expression(Scalar value);

        Expression(double value);

        Expression();

        Expression(const Expression& lhs, const Expression& rhs, Type type);

        Expression(const Expression& arg, Type type);

        Expression operator+(const Expression& other) const;

        Expression operator*(const Expression& other) const;

        Expression operator*(Scalar scalar) const;

        Expression operator*(double scalar) const;

        Expression operator-() const;

        Expression operator-(const Expression& other) const;

        bool operator<(const Expression& other) const;

        bool operator<(double x) const;

        bool operator>(const Expression& other) const;

        bool operator>(double x) const;

        bool operator==(const Expression& other) const;

        bool operator!=(const Expression& other) const;

        std::string toString() const;

        [[nodiscard]] Scalar getValue() const;

        [[nodiscard]] Scalar getDerivative() const;

        void differentiate(Scalar h) const;

        void resetDerivative() const;
    };
}

Delta::Expression operator*(double scalar, const Delta::Expression& expression);
Delta::Expression log(const Delta::Expression& expression);

#endif //DELTA_EXPRESSION_H
