#pragma once

#include <cstddef>
#include <initializer_list>
#include <iosfwd>

class Polynomial {
    double* coeffs_;
    int degree_;

    void trim();

public:
    Polynomial();
    Polynomial(const double* coeffs, int degree);
    Polynomial(std::initializer_list<double> coeffs);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    ~Polynomial();

    void swap(Polynomial& other) noexcept;
    Polynomial& operator=(Polynomial other);

    int degree() const;
    double get_coeff(int power) const;
    void set_coeff(int power, double value);

    void add(const Polynomial& other);
    void mul(const Polynomial& other);
    double evaluate(double x) const;
    void print(std::ostream& out) const;

    Polynomial derivative() const;
    Polynomial integral() const;

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;
};

void swap(Polynomial& a, Polynomial& b) noexcept;
