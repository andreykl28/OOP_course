#include "polynomial.h"
#include <cmath>
#include <iostream>
#include <utility>

void Polynomial::trim() {
    int d = degree_;
    while (d >= 0 && std::abs(coeffs_[d]) < 1e-12) {
        --d;
    }

    if (d < 0) {
        delete[] coeffs_;
        coeffs_ = nullptr;
        degree_ = -1;
        return;
    }

    if (d < degree_) {
        double* new_coeffs = new double[d + 1];
        for (int i = 0; i <= d; ++i) {
            new_coeffs[i] = coeffs_[i];
        }
        delete[] coeffs_;
        coeffs_ = new_coeffs;
        degree_ = d;
    }
}

Polynomial::Polynomial() : coeffs_(nullptr), degree_(-1) {}

Polynomial::Polynomial(const double* coeffs, int degree) : coeffs_(nullptr), degree_(-1) {
    if (coeffs != nullptr && degree >= 0) {
        degree_ = degree;
        coeffs_ = new double[degree_ + 1];
        for (int i = 0; i <= degree_; ++i) {
            coeffs_[i] = coeffs[i];
        }
        trim();
    }
}

Polynomial::Polynomial(std::initializer_list<double> coeffs) : coeffs_(nullptr), degree_(-1) {
    if (coeffs.size() > 0) {
        degree_ = static_cast<int>(coeffs.size()) - 1;
        coeffs_ = new double[degree_ + 1];
        int idx = 0;
        for (double val : coeffs) {
            coeffs_[idx++] = val;
        }
        trim();
    }
}

Polynomial::Polynomial(const Polynomial& other) : coeffs_(nullptr), degree_(other.degree_) {
    if (degree_ >= 0 && other.coeffs_ != nullptr) {
        coeffs_ = new double[degree_ + 1];
        for (int i = 0; i <= degree_; ++i) {
            coeffs_[i] = other.coeffs_[i];
        }
    }
}

Polynomial::Polynomial(Polynomial&& other) noexcept : coeffs_(other.coeffs_), degree_(other.degree_) {
    other.coeffs_ = nullptr;
    other.degree_ = -1;
}

Polynomial::~Polynomial() {
    delete[] coeffs_;
    coeffs_ = nullptr;
    degree_ = -1;
}

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(coeffs_, other.coeffs_);
    std::swap(degree_, other.degree_);
}

Polynomial& Polynomial::operator=(Polynomial other) {
    swap(other);
    return *this;
}

int Polynomial::degree() const {
    return degree_;
}

double Polynomial::get_coeff(int power) const {
    if (power < 0 || power > degree_ || coeffs_ == nullptr) {
        return 0.0;
    }
    return coeffs_[power];
}

void Polynomial::set_coeff(int power, double value) {
    if (power < 0) {
        return;
    }

    if (power > degree_) {
        if (std::abs(value) < 1e-12) {
            return;
        }
        double* new_coeffs = new double[power + 1]();
        for (int i = 0; i <= degree_; ++i) {
            new_coeffs[i] = coeffs_[i];
        }
        new_coeffs[power] = value;
        delete[] coeffs_;
        coeffs_ = new_coeffs;
        degree_ = power;
    } else {
        coeffs_[power] = value;
        if (power == degree_ && std::abs(value) < 1e-12) {
            trim();
        }
    }
}

void Polynomial::add(const Polynomial& other) {
    if (other.degree_ < 0) {
        return;
    }
    if (degree_ < 0) {
        *this = other;
        return;
    }

    int max_degree = (degree_ > other.degree_) ? degree_ : other.degree_;
    double* new_coeffs = new double[max_degree + 1]();

    for (int i = 0; i <= degree_; ++i) {
        new_coeffs[i] += coeffs_[i];
    }
    for (int i = 0; i <= other.degree_; ++i) {
        new_coeffs[i] += other.coeffs_[i];
    }

    delete[] coeffs_;
    coeffs_ = new_coeffs;
    degree_ = max_degree;
    trim();
}

void Polynomial::mul(const Polynomial& other) {
    if (degree_ < 0 || other.degree_ < 0) {
        delete[] coeffs_;
        coeffs_ = nullptr;
        degree_ = -1;
        return;
    }

    int new_degree = degree_ + other.degree_;
    double* new_coeffs = new double[new_degree + 1]();

    for (int i = 0; i <= degree_; ++i) {
        for (int j = 0; j <= other.degree_; ++j) {
            new_coeffs[i + j] += coeffs_[i] * other.coeffs_[j];
        }
    }

    delete[] coeffs_;
    coeffs_ = new_coeffs;
    degree_ = new_degree;
    trim();
}

double Polynomial::evaluate(double x) const {
    if (degree_ < 0 || coeffs_ == nullptr) {
        return 0.0;
    }

    double result = coeffs_[degree_];
    for (int i = degree_ - 1; i >= 0; --i) {
        result = result * x + coeffs_[i];
    }
    return result;
}

void Polynomial::print(std::ostream& out) const {
    if (degree_ < 0 || coeffs_ == nullptr) {
        out << "0";
        return;
    }

    bool first = true;
    for (int i = 0; i <= degree_; ++i) {
        double c = coeffs_[i];
        if (std::abs(c) < 1e-12) {
            continue;
        }

        if (first) {
            if (c < 0) {
                out << "-";
                c = -c;
            }
            first = false;
        } else {
            if (c < 0) {
                out << " - ";
                c = -c;
            } else {
                out << " + ";
            }
        }

        if (i == 0) {
            out << c;
        } else {
            if (std::abs(c - 1.0) > 1e-12) {
                out << c;
            }
            out << "x";
            if (i > 1) {
                out << "^" << i;
            }
        }
    }

    if (first) {
        out << "0";
    }
}

Polynomial Polynomial::derivative() const {
    if (degree_ <= 0 || coeffs_ == nullptr) {
        return Polynomial();
    }

    int new_degree = degree_ - 1;
    double* new_coeffs = new double[new_degree + 1];
    for (int i = 1; i <= degree_; ++i) {
        new_coeffs[i - 1] = coeffs_[i] * static_cast<double>(i);
    }

    Polynomial result(new_coeffs, new_degree);
    delete[] new_coeffs;
    return result;
}

Polynomial Polynomial::integral() const {
    if (degree_ < 0 || coeffs_ == nullptr) {
        return Polynomial();
    }

    int new_degree = degree_ + 1;
    double* new_coeffs = new double[new_degree + 1]();
    new_coeffs[0] = 0.0;
    for (int i = 0; i <= degree_; ++i) {
        new_coeffs[i + 1] = coeffs_[i] / (i + 1.0);
    }

    Polynomial result(new_coeffs, new_degree);
    delete[] new_coeffs;
    return result;
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (degree_ != other.degree_) {
        return false;
    }
    for (int i = 0; i <= degree_; ++i) {
        if (std::abs(coeffs_[i] - other.coeffs_[i]) > 1e-9) {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

void swap(Polynomial& a, Polynomial& b) noexcept {
    a.swap(b);
}

