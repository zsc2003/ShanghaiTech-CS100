#include "polynomial.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

// The following six special functions can all be defaulted.
// The compiler-synthesized version is enough.

Polynomial::Polynomial() = default;

Polynomial::Polynomial(const Polynomial &) = default;

Polynomial::Polynomial(Polynomial &&) noexcept = default;

Polynomial::~Polynomial() = default;

Polynomial &Polynomial::operator=(const Polynomial &) = default;

Polynomial &Polynomial::operator=(Polynomial &&) noexcept = default;

// If you want to write them manually:

// Polynomial::Polynomial() {}

// Polynomial::Polynomial(const Polynomial &p) : m_coeffs(p.m_coeffs) {}

// Polynomial::Polynomial(Polynomial &&p) noexcept : m_coeffs(std::move(p.m_coeffs)) {}

// Polynomial &operator=(const Polynomial &p) {
//     m_coeffs = p.m_coeffs;
//     return *this;
// }

// Polynomial &operator=(Polynomial &&p) noexcept {
//     m_coeffs = std::move(p.m_coeffs);
//     return *this;
// }

// Polynomial::~Polynomial() {}

// For explanation about move operations, see Piazza @238.

Polynomial::Polynomial(const std::vector<double> &coeffs) : m_coeffs(coeffs) {}

Polynomial::Polynomial(std::vector<double> &&coeffs) :
        m_coeffs(std::move(coeffs)) {}

Polynomial::Polynomial(std::initializer_list<double> coeffs) : m_coeffs(coeffs) {}

Polynomial::Polynomial(const std::string &path) {
    std::ifstream fin(path);
    double value;
    while (fin >> value)
        m_coeffs.push_back(value);
}

double& Polynomial::operator[](int index) {
    return m_coeffs[index];
}

const double& Polynomial::operator[](int index) const {
    return m_coeffs[index];
}

int Polynomial::size() const {
    return m_coeffs.size();
}

static inline Polynomial negate(const Polynomial &p) {
    auto ret = p;
    for (int i = 0; i != ret.size(); ++i)
        ret[i] = -ret[i];
    return ret;
}

Polynomial& Polynomial::operator+=(const Polynomial &p) {
    for (int i = 0; i < size() && i < p.size(); ++i)
        m_coeffs[i] += p[i];
    if (size() < p.size()) {
        for (int i = size(); i != p.size(); ++i)
            m_coeffs.push_back(p[i]);
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &p) const {
    return Polynomial(*this) += p;
}

Polynomial& Polynomial::operator-=(const Polynomial &p) {
    return *this += negate(p);
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
    return Polynomial(*this) -= p;
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
    std::vector<double> result(size() + p.size() - 1, 0);
    for (int i = 0; i < size(); ++i)
        for (int j = 0; j < p.size(); ++j)
            result[i + j] += m_coeffs[i] * p[j];
    return {result};
    // Equivalent to 'return Polynomial(result)'.
    // But we don't want to write the return-type again.
}

Polynomial Polynomial::operator*(double factor) const {
    std::vector<double> result;
    for (int i = 0; i < size(); ++i)
        result.push_back(m_coeffs[i] * factor);
    return {result};
}

Polynomial& Polynomial::operator*=(const Polynomial &p) {
    return *this = *this * p;
}

double Polynomial::operator()(double x) const {
    if (size() == 0)
        return 0;
    double result = m_coeffs[size() - 1];
    for (int i = size() - 2; i >= 0; --i) {
        result *= x;
        result += m_coeffs[i];
    }
    return result;
}