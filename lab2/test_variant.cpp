#include <gtest/gtest.h>
#include <sstream>
#include "polynomial.h"

TEST(PolynomialTest, DefaultConstructor) {
    Polynomial p;
    EXPECT_EQ(p.degree(), -1);
    EXPECT_DOUBLE_EQ(p.get_coeff(0), 0.0);
    EXPECT_DOUBLE_EQ(p.evaluate(5.0), 0.0);
}

TEST(PolynomialTest, ParametricConstructorAndTrim) {
    double c[] = {1.0, 2.0, 0.0, 0.0};
    Polynomial p(c, 3);
    EXPECT_EQ(p.degree(), 1);
    EXPECT_DOUBLE_EQ(p.get_coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(p.get_coeff(1), 2.0);
    EXPECT_DOUBLE_EQ(p.get_coeff(2), 0.0);
}

TEST(PolynomialTest, InitializerListConstructor) {
    Polynomial p{3.0, 0.0, 4.0};
    EXPECT_EQ(p.degree(), 2);
    EXPECT_DOUBLE_EQ(p.get_coeff(0), 3.0);
    EXPECT_DOUBLE_EQ(p.get_coeff(1), 0.0);
    EXPECT_DOUBLE_EQ(p.get_coeff(2), 4.0);
}

TEST(PolynomialTest, CopyConstructorDeepCopy) {
    Polynomial original{1.0, 2.0, 3.0};
    Polynomial copy(original);

    EXPECT_EQ(original, copy);

    copy.set_coeff(0, 99.0);
    EXPECT_DOUBLE_EQ(original.get_coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(copy.get_coeff(0), 99.0);
}

TEST(PolynomialTest, MoveConstructor) {
    Polynomial source{1.0, 2.0, 3.0};
    Polynomial target(std::move(source));

    EXPECT_EQ(target.degree(), 2);
    EXPECT_DOUBLE_EQ(target.get_coeff(2), 3.0);
    EXPECT_EQ(source.degree(), -1);
    EXPECT_DOUBLE_EQ(source.get_coeff(0), 0.0);
}

TEST(PolynomialTest, CopyAssignment) {
    Polynomial a{1.0, 2.0};
    Polynomial b{5.0, 6.0, 7.0};

    a = b;
    EXPECT_EQ(a, b);
    EXPECT_EQ(a.degree(), 2);
}

TEST(PolynomialTest, MoveAssignment) {
    Polynomial a{1.0, 2.0};
    Polynomial b{5.0, 6.0, 7.0};

    a = std::move(b);
    EXPECT_EQ(a.degree(), 2);
    EXPECT_DOUBLE_EQ(a.get_coeff(2), 7.0);
    EXPECT_EQ(b.degree(), -1);
}

TEST(PolynomialTest, SelfAssignment) {
    Polynomial a{2.0, 4.0, 6.0};
    a = a;
    EXPECT_EQ(a.degree(), 2);
    EXPECT_DOUBLE_EQ(a.get_coeff(0), 2.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(1), 4.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(2), 6.0);
}

TEST(PolynomialTest, AddLectureExample) {
    // a = 1 + 2x, b = x + x^2
    // a + b = 1 + 3x + x^2
    Polynomial a{1.0, 2.0};
    Polynomial b{0.0, 1.0, 1.0};

    a.add(b);
    EXPECT_EQ(a.degree(), 2);
    EXPECT_DOUBLE_EQ(a.get_coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(1), 3.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(2), 1.0);
}

TEST(PolynomialTest, AddWithZeroPolynomial) {
    Polynomial a{1.0, 2.0};
    Polynomial zero;

    a.add(zero);
    EXPECT_EQ(a.degree(), 1);
    EXPECT_DOUBLE_EQ(a.get_coeff(0), 1.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(1), 2.0);

    zero.add(a);
    EXPECT_EQ(zero, a);
}

TEST(PolynomialTest, AddLeadingTermsCancellation) {
    Polynomial a{1.0, 2.0, 5.0};
    Polynomial b{3.0, 1.0, -5.0};

    a.add(b);
    EXPECT_EQ(a.degree(), 1);
    EXPECT_DOUBLE_EQ(a.get_coeff(0), 4.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(1), 3.0);
}

TEST(PolynomialTest, MulLectureExample) {
    // a = 1 + 2x, b = x + x^2
    // a * b = x + 3x^2 + 2x^3
    Polynomial a{1.0, 2.0};
    Polynomial b{0.0, 1.0, 1.0};

    a.mul(b);
    EXPECT_EQ(a.degree(), 3);
    EXPECT_DOUBLE_EQ(a.get_coeff(0), 0.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(1), 1.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(2), 3.0);
    EXPECT_DOUBLE_EQ(a.get_coeff(3), 2.0);
}

TEST(PolynomialTest, MulWithZero) {
    Polynomial a{1.0, 2.0, 3.0};
    Polynomial zero;

    a.mul(zero);
    EXPECT_EQ(a.degree(), -1);
}

TEST(PolynomialTest, EvaluateLectureExample) {
    // 1 + 3x + x^2 at x = 2: 1 + 6 + 4 = 11
    Polynomial p{1.0, 3.0, 1.0};
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 11.0);
    EXPECT_DOUBLE_EQ(p.evaluate(0.0), 1.0);
    EXPECT_DOUBLE_EQ(p.evaluate(-1.0), -1.0);
}

TEST(PolynomialTest, DerivativeLectureExample) {
    // (1 + 2x + 3x^2).derivative() -> 2 + 6x
    Polynomial p{1.0, 2.0, 3.0};
    Polynomial d = p.derivative();

    EXPECT_EQ(d.degree(), 1);
    EXPECT_DOUBLE_EQ(d.get_coeff(0), 2.0);
    EXPECT_DOUBLE_EQ(d.get_coeff(1), 6.0);
}

TEST(PolynomialTest, DerivativeConstantAndZero) {
    Polynomial constant_p{7.0};
    Polynomial d1 = constant_p.derivative();
    EXPECT_EQ(d1.degree(), -1);

    Polynomial zero_p;
    Polynomial d2 = zero_p.derivative();
    EXPECT_EQ(d2.degree(), -1);
}

TEST(PolynomialTest, IntegralLectureExample) {
    // (2x).integral() -> x^2 (свободный член 0)
    Polynomial p{0.0, 2.0};
    Polynomial integ = p.integral();

    EXPECT_EQ(integ.degree(), 2);
    EXPECT_DOUBLE_EQ(integ.get_coeff(0), 0.0);
    EXPECT_DOUBLE_EQ(integ.get_coeff(1), 0.0);
    EXPECT_DOUBLE_EQ(integ.get_coeff(2), 1.0);
}

TEST(PolynomialTest, IntegralHigherDegree) {
    // (1 + 2x + 3x^2).integral() -> x + x^2 + x^3
    Polynomial p{1.0, 2.0, 3.0};
    Polynomial integ = p.integral();

    EXPECT_EQ(integ.degree(), 3);
    EXPECT_DOUBLE_EQ(integ.get_coeff(0), 0.0);
    EXPECT_DOUBLE_EQ(integ.get_coeff(1), 1.0);
    EXPECT_DOUBLE_EQ(integ.get_coeff(2), 1.0);
    EXPECT_DOUBLE_EQ(integ.get_coeff(3), 1.0);
}

TEST(PolynomialTest, IntegralZeroPolynomial) {
    Polynomial zero;
    Polynomial integ = zero.integral();
    EXPECT_EQ(integ.degree(), -1);
}

TEST(PolynomialTest, FundamentalTheoremOfCalculus) {
    // derivative(integral(P(x))) == P(x)
    Polynomial p{4.0, -2.5, 7.0, 1.2};
    Polynomial roundtrip = p.integral().derivative();
    EXPECT_EQ(p, roundtrip);
}

TEST(PolynomialTest, PrintFormatting) {
    std::ostringstream ss1;
    Polynomial p1{1.0, 2.0};
    p1.print(ss1);
    EXPECT_EQ(ss1.str(), "1 + 2x");

    std::ostringstream ss2;
    Polynomial p2{0.0, 1.0, 1.0};
    p2.print(ss2);
    EXPECT_EQ(ss2.str(), "x + x^2");

    std::ostringstream ss3;
    Polynomial p3;
    p3.print(ss3);
    EXPECT_EQ(ss3.str(), "0");
}
