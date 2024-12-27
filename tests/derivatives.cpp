//
// Created by Zakarie Aloui on 28/11/2023.
//

#include <catch2/catch_all.hpp>
#include <Eigen/Dense>
#include "Expression.h"

using Delta::Expression;
using Eigen::Matrix;


TEST_CASE("Derivative of a sum", "[DerivativeSum]") {
    Expression a(0), b(0), c(-1), d(2), e(1.5), f(-1.5), g({1, 2}), h({0, -1});

    Expression x(a + b);
    x.differentiate(1);
    REQUIRE(x.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(a.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(b.getDerivative() == Delta::Scalar{1, 0});
    a.resetDerivative();
    b.resetDerivative();

    Expression y(c + d + e);
    y.differentiate(1);
    REQUIRE(y.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(c.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(d.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(e.getDerivative() == Delta::Scalar{1, 0});
    c.resetDerivative();
    d.resetDerivative();
    e.resetDerivative();

    Expression z(f + f + g + h - h);
    z.differentiate(1);
    REQUIRE(z.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(f.getDerivative() == Delta::Scalar{2, 0});
    REQUIRE(g.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(h.getDerivative() == Delta::Scalar{0, 0});
    f.resetDerivative();
    g.resetDerivative();
    h.resetDerivative();

    Expression w(h * a + b * g + c * b);
    w.differentiate(1);
    REQUIRE(w.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(h.getDerivative() == a.getValue());
    REQUIRE(a.getDerivative() == h.getValue());
    REQUIRE(b.getDerivative() == g.getValue() + c.getValue());
    REQUIRE(g.getDerivative() == b.getValue());
    REQUIRE(c.getDerivative() == b.getValue());
}

TEST_CASE("Derivative of a product", "[DerivativeProduct]") {
    Expression a(0), b(0), c(-1), d(2), e(1.5), f(-1.5), g({1, 2}), h({0, -1});

    Expression x(a * b);
    x.differentiate(1);
    REQUIRE(x.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(a.getDerivative() == b.getValue());
    REQUIRE(b.getDerivative() == a.getValue());
    a.resetDerivative();
    b.resetDerivative();

    Expression y(c * d * e);
    y.differentiate(1);
    REQUIRE(y.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(c.getDerivative() == d.getValue() * e.getValue());
    REQUIRE(d.getDerivative() == c.getValue() * e.getValue());
    REQUIRE(e.getDerivative() == c.getValue() * d.getValue());
    c.resetDerivative();
    d.resetDerivative();
    e.resetDerivative();

    Expression z(f * f * g);
    z.differentiate(1);
    REQUIRE(z.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(f.getDerivative() == Delta::Scalar{2, 0} * f.getValue() * g.getValue());
    REQUIRE(g.getDerivative() == f.getValue() * f.getValue());
    f.resetDerivative();
    g.resetDerivative();

    Expression w(g * h * (a + b) * (g + b));
    w.differentiate(1);
    REQUIRE(w.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(h.getDerivative() == (g * (a + b) * (g + b)).getValue());
    REQUIRE(a.getDerivative() == (g * h * (g + b)).getValue());
    REQUIRE(b.getDerivative() == (g * h * (a + g) + (2 * b)).getValue());
    REQUIRE(g.getDerivative() == (h * (a + b) * b * 2 * g).getValue());
}

TEST_CASE("Derivative of a logarithm", "[DerivativeLog]") {
    Expression a(2.), b(0.5), c(12.5), d({0, 1});

    Expression x(log(a));
    x.differentiate(1);
    REQUIRE(a.getValue() == 2.);
    REQUIRE(x.getValue() == log(a.getValue()));
    REQUIRE(x.getDerivative() == Delta::Scalar{1, 0});
    REQUIRE(a.getDerivative() == 1. / a.getValue());
    a.resetDerivative();
    x.resetDerivative();

    Expression y(log(x));
    y.differentiate(1);
    REQUIRE(y.getDerivative() == 1.);
    REQUIRE(x.getDerivative() == 1.0 / x.getValue());
    REQUIRE(a.getDerivative() == 1.0 / (a.getValue() * x.getValue()));
    y.resetDerivative();
    x.resetDerivative();
    a.resetDerivative();

    Expression w(log(c));
    Expression z(log(log(w) * w));
    z.differentiate(1);
    REQUIRE(z.getDerivative() == 1.0);
    REQUIRE(abs(w.getDerivative() - (log(w) + 1.).getValue() / (w * log(w)).getValue()) < 1e-10);
    REQUIRE(abs(c.getDerivative() - (log(log(c)) + 1.).getValue() / (c * log(c) * log(log(c))).getValue()) < 1e-10);
    w.resetDerivative();
    z.resetDerivative();
    c.resetDerivative();

    Expression u(d * log(c));
    u.differentiate(1);
    REQUIRE(c.getDerivative() == d.getValue() / c.getValue());
}