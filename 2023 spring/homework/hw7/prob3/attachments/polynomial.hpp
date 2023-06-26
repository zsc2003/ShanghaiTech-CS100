#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>
#include <cstdio>

class Polynomial
{
  // `m_coeffs` stores the coefficients.
  // Note: This is not the unique correct implementation.
  // For example, you may separate the constant term from others,
  // and store the constant term using another variable.
private:
  std::vector<double> m_coeffs;

public:
  Polynomial() : m_coeffs()
  {
    m_coeffs.push_back(0);
    adjust();
  }
  ~Polynomial() {}
  explicit Polynomial(const std::vector<double> &other) : m_coeffs(other) { adjust(); }
  explicit Polynomial(std::vector<double> &&other) : m_coeffs(std::move(other)) { adjust(); }
  
  template <typename InputIterator>
  explicit Polynomial(InputIterator begin, InputIterator end)
      : m_coeffs(begin, end) { adjust(); } 
  
  static auto isZero(double x)
  {
    static constexpr auto eps = 1e-8;
    return x < eps && -x < eps;
  }

  // Remove trailing zeros, to ensure that the coefficient of the term with
  // the highest order is non-zero.
  // Note that a polynomial should have at least one term, which is the
  // constant. It should not be removed even if it is zero.
  // If m_coeffs is empty, adjust() should also insert a zero into m_coeffs.
  void adjust()
  {
    // YOUR CODE HERE
    for (std::size_t i = m_coeffs.size() - 1; i != (std::size_t)-1; --i)
    {
      if (!isZero(m_coeffs[i]))
        break;
      m_coeffs.pop_back();
    }
    if (m_coeffs.empty())
      m_coeffs.push_back(0.0f);
  }

  // Other members ...
  std::size_t deg() const
  {
    return m_coeffs.size() - 1;
  }
  double operator[](std::size_t pos) const
  {
    return m_coeffs[pos];
  }
  void setCoeff(std::size_t pos, double val)
  {
    if (deg() < pos)
    {
      m_coeffs.resize(pos + 1);
    }
    m_coeffs[pos] = val;
    adjust();
  }

  double operator()(double x) const
  {
    double ret = 0.0;
    double tmp = 1.0;
    for (std::size_t i = 0; i < m_coeffs.size(); ++i)
    {
      ret += tmp * m_coeffs[i];
      tmp *= x;
    }
    // printf("%lld\n", m_coeffs.size());
    return ret;
  }

  Polynomial derivative() const
  {
    std::vector<double> ret{};
    for (std::size_t i = 1; i < m_coeffs.size(); ++i)
    {
      ret.push_back(m_coeffs[i] * double(i));
    }
    return Polynomial(std::move(ret));
  }
  Polynomial integral() const
  {
    std::vector<double> ret{};
    ret.push_back(0);
    for (std::size_t i = 0; i < m_coeffs.size(); ++i)
    {
      ret.push_back(m_coeffs[i] / double(i + 1));
    }
    return Polynomial(std::move(ret));
  }
  friend bool operator==(const Polynomial &, const Polynomial &);
  friend bool operator!=(const Polynomial &, const Polynomial &);
  friend Polynomial operator-(const Polynomial &);
  friend Polynomial operator-(const Polynomial &, const Polynomial &);
  friend Polynomial operator+(const Polynomial &, const Polynomial &);
  friend Polynomial &operator+=(Polynomial &, const Polynomial &);
  friend Polynomial &operator-=(Polynomial &, const Polynomial &);
  friend Polynomial operator*(const Polynomial &, const Polynomial &);
  friend Polynomial &operator*=(Polynomial &, const Polynomial &);
};
// Add non-member functions if you need.
Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs)
{
  std::vector<double> ret(lhs.m_coeffs.size() + rhs.m_coeffs.size() - 1, 0.0);
  for (std::size_t i = 0; i < lhs.m_coeffs.size(); ++i)
  {
    for (std::size_t j = 0; j < rhs.m_coeffs.size(); ++j)
    {
      ret[i + j] += lhs.m_coeffs[i] * rhs.m_coeffs[j];
    }
  }
  return Polynomial(std::move(ret));
}
Polynomial &operator*=(Polynomial &lhs, const Polynomial &rhs)
{
  lhs = lhs * rhs;
  return lhs;
}
Polynomial &operator+=(Polynomial &lhs, const Polynomial &rhs)
{
  lhs = lhs + rhs;
  return lhs;
}
Polynomial &operator-=(Polynomial &lhs, const Polynomial &rhs)
{
  lhs = lhs - rhs;
  return lhs;
}
Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs)
{
  std::vector<double> ret(std::max(lhs.m_coeffs.size(), rhs.m_coeffs.size()), 0.0);
  if (lhs.m_coeffs.size() > rhs.m_coeffs.size())
  {
    for (std::size_t i = 0; i < rhs.m_coeffs.size(); ++i)
    {
      ret[i] = (lhs.m_coeffs[i] + rhs.m_coeffs[i]);
    }
    for (std::size_t i = rhs.m_coeffs.size(); i < lhs.m_coeffs.size(); ++i)
    {
      ret[i] = (lhs.m_coeffs[i]);
    }
  }
  else
  {
    for (std::size_t i = 0; i < lhs.m_coeffs.size(); ++i)
    {
      ret[i] = (lhs.m_coeffs[i] + rhs.m_coeffs[i]);
    }
    for (std::size_t i = lhs.m_coeffs.size(); i < rhs.m_coeffs.size(); ++i)
    {
      ret[i] = (rhs.m_coeffs[i]);
    }
  }
  return Polynomial(std::move(ret));
}
Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs)
{
  return std::move(lhs + (-rhs));
}
bool operator==(const Polynomial &lhs, const Polynomial &rhs)
{
  if (lhs.deg() != rhs.deg())
    return false;
  for (std::size_t i = 0; i <= lhs.deg(); ++i)
  {
    if (!lhs.isZero(lhs.m_coeffs[i] - rhs.m_coeffs[i]))
      return false;
  }
  return true;
}
bool operator!=(const Polynomial &lhs, const Polynomial &rhs)
{
  return !(rhs == lhs);
}
Polynomial operator-(const Polynomial &lhs)
{
  std::vector<double> ret{};
  for (std::size_t i = 0; i < lhs.m_coeffs.size(); ++i)
  {
    ret.push_back(-lhs.m_coeffs[i]);
  }
  return Polynomial(std::move(ret));
}
#endif // POLYNOMIAL_HPP