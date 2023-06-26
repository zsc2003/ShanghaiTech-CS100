#ifndef CS100_HW_MATRIX_HPP
#define CS100_HW_MATRIX_HPP

#include <algorithm>
#include <cstddef>

class Matrix {
 public:
  typedef double Scalar;
  typedef std::size_t Index;

  explicit Matrix(Index rows, Index cols);
  Matrix(const Matrix &other);
  // copy and swap
  void swap(Matrix &other);
  Matrix &operator=(const Matrix &other);
  ~Matrix();
  Index rows() const;
  Index cols() const;
  Scalar &at(Index r, Index c);
  const Scalar &at(Index r, Index c) const;
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix transpose() const;
  // Block of size p x q, starting at (r,c)
  Matrix block(Index r, Index c, Index p, Index q) const;
  Scalar trace() const;
  Scalar determinant() const;

 private:
  Matrix _submatrix(Index i, Index j) const;

  Index m_rows;
  Index m_cols;
  Scalar **m_data;
};

Matrix::Matrix(Index rows, Index cols)
    : m_rows(rows), m_cols(cols), m_data(new Scalar *[rows]) {
  for (Index i = 0; i < rows; ++i)
    m_data[i] = new Scalar[cols]{};
}

Matrix::Matrix(const Matrix &other)
    : m_rows(other.rows()), m_cols(other.cols()),
      m_data(new Scalar *[other.rows()]) {
  for (Index i = 0; i < other.rows(); ++i) {
    m_data[i] = new Scalar[other.cols()];
    std::copy(other.m_data[i], other.m_data[i] + other.cols(), m_data[i]);
  }
}

Matrix::~Matrix() {
  for (Index i = 0; i < rows(); ++i)
    delete[] m_data[i];
  delete[] m_data;
}

Matrix::Index Matrix::rows() const {
  return m_rows;
}

Matrix::Index Matrix::cols() const {
  return m_cols;
}

Matrix::Scalar &Matrix::at(Index r, Index c) {
  return m_data[r][c];
}

const Matrix::Scalar &Matrix::at(Index r, Index c) const {
  return m_data[r][c];
}

void Matrix::swap(Matrix &other) {
  using std::swap;
  swap(m_rows, other.m_rows);
  swap(m_cols, other.m_cols);
  swap(m_data, other.m_data);
}

Matrix &Matrix::operator=(const Matrix &other) {
  Matrix(other).swap(*this);
  return *this;
}

Matrix Matrix::operator+(const Matrix &other) const {
  Matrix m(*this);
  for (Index i = 0; i < rows(); ++i)
    for (Index j = 0; j < cols(); ++j)
      m.at(i, j) += other.at(i, j);
  return m;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix m(*this);
  for (Index i = 0; i < rows(); ++i)
    for (Index j = 0; j < cols(); ++j)
      m.at(i, j) -= other.at(i, j);
  return m;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix m(rows(), other.cols());
  for (Index i = 0; i < rows(); i++)
    for (Index j = 0; j < other.cols(); j++)
      for (Index k = 0; k < cols(); k++)
        m.at(i, j) += at(i, k) * other.at(k, j);
  return m;
}

Matrix Matrix::transpose() const {
  Matrix m(cols(), rows());
  for (Index i = 0; i < rows(); i++)
    for (Index j = 0; j < cols(); j++)
      m.at(j, i) = at(i, j);
  return m;
}

Matrix Matrix::block(Index r, Index c, Index p, Index q) const {
  Matrix m(p, q);
  for (Index i = 0; i < p; i++)
    for (Index j = 0; j < q; j++)
      m.at(i, j) = at(r + i, c + j);
  return m;
}

Matrix::Scalar Matrix::trace() const {
  Scalar ret = 0;
  for (Index i = 0; i < rows(); i++)
    ret += at(i, i);
  return ret;
}

Matrix::Scalar Matrix::determinant() const {
  if (rows() == 1) {
    return at(0, 0);
  } else if (rows() == 2) {
    return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
  } else {
    Scalar det = 0;
    Scalar sign = 1;
    for (Index i = 0; i < rows(); i++) {
      Matrix submatrix = _submatrix(0, i);
      det += sign * at(0, i) * submatrix.determinant();
      sign = -sign;
    }
    return det;
  }
}

Matrix Matrix::_submatrix(Index i, Index j) const {
  Matrix m(rows() - 1, cols() - 1);
  Index x = 0, y = 0;
  for (Index r = 0; r < rows(); r++) {
    for (Index c = 0; c < cols(); c++) {
      if (r != i && c != j) {
        m.at(y, x) = at(r, c);
        x++;
        if (x == rows() - 1) {
          x = 0;
          y++;
        }
      }
    }
  }
  return m;
}

#endif // CS100_HW_MATRIX_HPP