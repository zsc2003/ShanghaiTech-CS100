#ifndef CS100_HW_MATRIX_HPP
#define CS100_HW_MATRIX_HPP

#include <cstddef>
#include <vector>

class Matrix {
 public:
  typedef double Scalar;
  typedef std::size_t Index;

  explicit Matrix(Index rows, Index cols);
  Matrix(const Matrix &other);
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
  Matrix block(Index r, Index c, Index p,
               Index q) const; // Block of size p x q, starting at (r,c)
  Scalar trace() const;
  Scalar determinant() const;

 private:
  Matrix _submatrix(Index i, Index j) const;

  Index m_rows;
  Index m_cols;
  std::vector<Scalar> m_data;
};

Matrix::Matrix(Index rows, Index cols)
    : m_rows(rows), m_cols(cols), m_data(rows * cols) {}

Matrix::Matrix(const Matrix &other) = default;

Matrix::~Matrix() = default;

Matrix &Matrix::operator=(const Matrix &other) = default;

Matrix::Index Matrix::rows() const {
  return m_rows;
}

Matrix::Index Matrix::cols() const {
  return m_cols;
}

Matrix::Scalar &Matrix::at(Index r, Index c) {
  return m_data[cols() * r + c];
}

const Matrix::Scalar &Matrix::at(Index r, Index c) const {
  return m_data[cols() * r + c];
}

Matrix Matrix::operator+(const Matrix &other) const {
  Matrix m(rows(), cols());
  for (Index i = 0; i < rows() * cols(); i++) {
    m.m_data[i] = m_data[i] + other.m_data[i];
  }
  return m;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix m(rows(), cols());
  for (Index i = 0; i < rows() * cols(); i++) {
    m.m_data[i] = m_data[i] - other.m_data[i];
  }
  return m;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix m(rows(), other.cols());
  for (Index r = 0; r < rows(); r++) {
    for (Index c = 0; c < other.cols(); c++) {
      m.at(r, c) = 0;
      for (Index k = 0; k < cols(); k++) {
        m.at(r, c) += at(r, k) * other.at(k, c);
      }
    }
  }
  return m;
}

Matrix Matrix::transpose() const {
  Matrix m(cols(), rows());
  for (Index r = 0; r < rows(); r++) {
    for (Index c = 0; c < cols(); c++) {
      m.at(c, r) = at(r, c);
    }
  }
  return m;
}

Matrix Matrix::block(Index r, Index c, Index p, Index q) const {
  Matrix m(p, q);
  for (Index i = 0; i < p; i++) {
    for (Index j = 0; j < q; j++) {
      m.at(i, j) = at(r + i, c + j);
    }
  }
  return m;
}

Matrix::Scalar Matrix::trace() const {
  Scalar ret = 0;
  for (Index i = 0; i < rows(); i++) {
    ret += at(i, i);
  }
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