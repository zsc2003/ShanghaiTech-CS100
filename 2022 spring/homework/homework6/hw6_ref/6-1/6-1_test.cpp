#define main __student_main_function_
#define _ONLINE_JUDGE

/******************************************/

// PASTE OR #include YOUR CODE HERE.

/******************************************/

#include <iostream>
#include <type_traits>

#ifdef OJ_ASSERT
#undef OJ_ASSERT
#endif
#define OJ_ASSERT(x)                                                           \
  {                                                                            \
    if (!(x)) {                                                                \
      std::cout << "Wrong answer at line " << __LINE__ << std::endl;           \
      return;                                                                  \
    }                                                                          \
  }
#undef main

void __attribute__((optimize("O0"))) test1() {
  // test constructor
  Matrix m1(1, 1);
  Matrix m2(10, 1);
  Matrix m3(50, 30);
  OJ_ASSERT(m1.rows() == 1 && m1.cols() == 1);
  OJ_ASSERT(m2.rows() == 10 && m2.cols() == 1);
  OJ_ASSERT(m3.rows() == 50 && m3.cols() == 30);

  OJ_ASSERT(std::abs(m1.at(0, 0)) < 1e-9);

  const Matrix &m1cr = m1;
  OJ_ASSERT(std::abs(m1cr.at(0, 0)) < 1e-9);

  Matrix m4(5, 6);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      m4.at(i, j) = (i + j) / 2.0;
    }
  }

  const Matrix &m4cr = m4;
  Matrix m5(m4cr);
  OJ_ASSERT(m5.rows() == 5 && m5.cols() == 6);
  const Matrix &m5cr = m5;
  OJ_ASSERT(m5cr.rows() == 5 && m5cr.cols() == 6);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      OJ_ASSERT(m5.at(i, j) == (i + j) / 2.0);
      const double &t = m5.at(i, j);
      OJ_ASSERT(t == (i + j) / 2.0);
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      m4.at(i, j) += 1.0;
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      OJ_ASSERT(m4.at(i, j) == (i + j) / 2.0 + 1.0);
      OJ_ASSERT(m5.at(i, j) == (i + j) / 2.0);
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      m5.at(i, j) -= 1.0;
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      OJ_ASSERT(m4.at(i, j) == (i + j) / 2.0 + 1.0);
      OJ_ASSERT(m5.at(i, j) == (i + j) / 2.0 - 1.0);
    }
  }
}

void __attribute__((optimize("O0"))) test2() {
  // test assignment operator
  Matrix m1(3, 8);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      m1.at(i, j) = 0.5 * i * j;
    }
  }

  Matrix m2(1, 2);
  const Matrix &m1cr = m1;
  m2 = m1cr;
  OJ_ASSERT(m2.rows() == 3 && m2.cols() == 8);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      OJ_ASSERT(m1.at(i, j) == 0.5 * i * j);
      OJ_ASSERT(m2.at(i, j) == 0.5 * i * j);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      m1.at(i, j) += 1.0;
      m2.at(i, j) -= 1.0;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      OJ_ASSERT(m1.at(i, j) == 0.5 * i * j + 1.0);
      OJ_ASSERT(m2.at(i, j) == 0.5 * i * j - 1.0);
    }
  }

  m1 = m1;
  OJ_ASSERT(m1.rows() == 3 && m2.cols() == 8);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      OJ_ASSERT(m1.at(i, j) == 0.5 * i * j + 1.0);
    }
  }
}

void __attribute__((optimize("O0"))) test3() {
  // test operator+
  Matrix m1(4, 6), m2(4, 6);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      m1.at(i, j) = 2 * i + 0.5 * j;
      m2.at(i, j) = 0.5 * i + 2 * j;
    }
  }
  const Matrix &m1cr = m1, &m2cr = m2;
  Matrix m3 = m1cr + m2cr;
  OJ_ASSERT(m3.rows() == 4 && m3.cols() == 6);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      OJ_ASSERT(m3.at(i, j) == m1.at(i, j) + m2.at(i, j));
      OJ_ASSERT(m3.at(i, j) == 2.5 * i + 2.5 * j);
    }
  };
  m3 = m1 + m2 + m3 + m3;
  OJ_ASSERT(m3.rows() == 4 && m3.cols() == 6);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      OJ_ASSERT(m3.at(i, j) == 7.5 * i + 7.5 * j);
    }
  }
}

void __attribute__((optimize("O0"))) test4() {
  // test operator-
  Matrix m1(6, 4), m2(6, 4);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      m1.at(i, j) = 2 * i + 0.5 * j;
      m2.at(i, j) = 0.5 * i + 2 * j;
    }
  }
  const Matrix &m1cr = m1, &m2cr = m2;
  Matrix m3 = m1cr - m2cr;
  OJ_ASSERT(m3.rows() == 6 && m3.cols() == 4);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      OJ_ASSERT(m3.at(i, j) == m1.at(i, j) - m2.at(i, j));
      OJ_ASSERT(m3.at(i, j) == 1.5 * i - 1.5 * j);
    }
  };
  m3 = m1 + m2 - m3 + m3;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      OJ_ASSERT(m3.at(i, j) == 2.5 * i + 2.5 * j);
    }
  }
}

void __attribute__((optimize("O0"))) test5() {
  // test operator*
  constexpr double eps = 1e-9;
  Matrix m1(5, 5), m2(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m1.at(i, j) = i + j;
      m2.at(i, j) = i - j;
    }
  }
  const Matrix &m1cr = m1, &m2cr = m2;
  Matrix m3 = m1cr * m2cr;
  OJ_ASSERT(m3.rows() == 5 && m3.cols() == 5);
  double ans1[5][5] = {{30, 20, 10, 0, -10},
                       {40, 25, 10, -5, -20},
                       {50, 30, 10, -10, -30},
                       {60, 35, 10, -15, -40},
                       {70, 40, 10, -20, -50}};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      OJ_ASSERT(std::abs(m3.at(i, j) - ans1[i][j]) < eps);
    }
  }
  m3 = m1 * m2 * m3;
  double ans2[5][5] = {{1500., 1000., 500., 0., -500.},
                       {1000., 750., 500., 250., 0.},
                       {500., 500., 500., 500., 500.},
                       {0., 250., 500., 750., 1000.},
                       {-500., 0., 500., 1000., 1500.}};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      OJ_ASSERT(std::abs(m3.at(i, j) - ans2[i][j]) < eps);
    }
  }
  m3 = (m1 + m2) * (m1 - m2) + m2 * m2;
  double ans3[5][5] = {{-30., -20., -10., 0., 10.},
                       {-20., 5., 30., 55., 80.},
                       {-10., 30., 70., 110., 150.},
                       {0., 55., 110., 165., 220.},
                       {10., 80., 150., 220., 290.}};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      OJ_ASSERT(std::abs(m3.at(i, j) - ans3[i][j]) < eps);
    }
  }

  Matrix m4(2, 3), m5(3, 2);
  m4.at(0, 0) = 1;
  m4.at(0, 1) = 2;
  m4.at(0, 2) = 3;
  m4.at(1, 0) = 4;
  m4.at(1, 1) = 5;
  m4.at(1, 2) = 6;
  m5.at(0, 0) = 1;
  m5.at(1, 0) = 3;
  m5.at(2, 0) = 5;
  m5.at(0, 1) = 2;
  m5.at(1, 1) = 4;
  m5.at(2, 1) = 6;
  m3 = m4 * m5;

  OJ_ASSERT(m3.rows() == 2 && m3.cols() == 2);
  OJ_ASSERT(std::abs(m3.at(0, 0) - 22) < eps);
  OJ_ASSERT(std::abs(m3.at(0, 1) - 28) < eps);
  OJ_ASSERT(std::abs(m3.at(1, 0) - 49) < eps);
  OJ_ASSERT(std::abs(m3.at(1, 1) - 64) < eps);

  m3 = m5 * m4;
  OJ_ASSERT(m3.rows() == 3 && m3.cols() == 3);
  OJ_ASSERT(std::abs(m3.at(0, 0) - 9) < eps);
  OJ_ASSERT(abs(m3.at(0, 1) - 12) < eps);
  OJ_ASSERT(abs(m3.at(0, 2) - 15) < eps);
  OJ_ASSERT(std::abs(m3.at(1, 0) - 19) < eps);
  OJ_ASSERT(abs(m3.at(1, 1) - 26) < eps);
  OJ_ASSERT(abs(m3.at(1, 2) - 33) < eps);
  OJ_ASSERT(std::abs(m3.at(2, 0) - 29) < eps);
  OJ_ASSERT(abs(m3.at(2, 1) - 40) < eps);
  OJ_ASSERT(abs(m3.at(2, 2) - 51) < eps);
}

void __attribute__((optimize("O0"))) test6() {
  // test transpose
  Matrix m1(1, 5), m2(4, 6), m3(10, 10);
  for (int i = 0; i < 5; i++) {
    m1.at(0, i) = i;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      m2.at(i, j) = 1.5 * i + j;
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      m3.at(i, j) = 1.0 * i * i + j;
    }
  }

  const Matrix &m1cr = m1;
  Matrix m4 = m1cr.transpose();
  OJ_ASSERT(m4.rows() == 5 && m4.cols() == 1);
  for (int i = 0; i < 5; i++) {
    OJ_ASSERT(m4.at(i, 0) == i);
  }
  m4 = m2.transpose();
  OJ_ASSERT(m4.rows() == 6 && m4.cols() == 4);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; ++j) {
      OJ_ASSERT(m4.at(i, j) == 1.5 * j + i);
    }
  }
  m4 = m3.transpose();
  OJ_ASSERT(m4.rows() == 10 && m4.cols() == 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      OJ_ASSERT(m4.at(i, j) == j * j + i);
    }
  }
}

void __attribute__((optimize("O0"))) test7() {
  // test block
  Matrix m1(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m1.at(i, j) = i + j;
    }
  }
  // 0 1 2 3 4
  // 1 2 3 4 5
  // 2 3 4 5 6
  // 3 4 5 6 7
  // 4 5 6 7 8
  const Matrix &m1cr = m1;
  Matrix m2 = m1cr.block(0, 0, 2, 2);
  OJ_ASSERT(m2.rows() == 2 && m2.cols() == 2);
  OJ_ASSERT(m2.at(0, 0) == 0);
  OJ_ASSERT(m2.at(0, 1) == 1);
  OJ_ASSERT(m2.at(1, 0) == 1);
  OJ_ASSERT(m2.at(1, 1) == 2);

  m2 = m1.block(3, 1, 2, 1);
  OJ_ASSERT(m2.rows() == 2 && m2.cols() == 1);
  OJ_ASSERT(m2.at(0, 0) == 4);
  OJ_ASSERT(m2.at(1, 0) == 5);

  m2 = m1.block(0, 1, 2, 4);
  OJ_ASSERT(m2.rows() == 2 && m2.cols() == 4);
  OJ_ASSERT(m2.at(0, 0) == 1);
  OJ_ASSERT(m2.at(0, 1) == 2);
  OJ_ASSERT(m2.at(0, 2) == 3);
  OJ_ASSERT(m2.at(0, 3) == 4);
  OJ_ASSERT(m2.at(1, 0) == 2);
  OJ_ASSERT(m2.at(1, 1) == 3);
  OJ_ASSERT(m2.at(1, 2) == 4);
  OJ_ASSERT(m2.at(1, 3) == 5);

  m2 = m1.block(3, 3, 1, 1);
  m2.at(0, 0) = -1;
  OJ_ASSERT(m2.rows() == 1 && m2.cols() == 1);
  OJ_ASSERT(m1.at(3, 3) == 6);
}

void __attribute__((optimize("O0"))) test8() {
  // test trace
  constexpr double eps = 1e-9;
  Matrix m(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m.at(i, j) = 0.5 * (i + j);
    }
  }
  const Matrix &mcr = m;
  OJ_ASSERT(std::abs(mcr.trace() - 10) < eps);
  m.at(0, 0) = -10.5;
  OJ_ASSERT(std::abs(mcr.trace() - -0.5) < eps);
  m.at(1, 0) = 3.1;
  OJ_ASSERT(std::abs(mcr.trace() - -0.5) < eps);
  m.at(3, 3) = 1.23;
  OJ_ASSERT(std::abs(mcr.trace() - -2.27) < eps);
}

void __attribute__((optimize("O0"))) test9() {
  // test determinant
  constexpr double eps = 1e-9;
  Matrix m1(1, 1);
  m1.at(0, 0) = 3.14;
  const Matrix &m1cr = m1;
  OJ_ASSERT(std::abs(m1cr.determinant() - 3.14) < eps);

  Matrix m2(2, 2);
  m2.at(0, 0) = 1;
  m2.at(0, 1) = 0;
  m2.at(1, 0) = 0;
  m2.at(1, 1) = 1;
  OJ_ASSERT(std::abs(m2.determinant() - 1) < eps);

  m2.at(0, 0) = -1;
  m2.at(0, 1) = 1;
  m2.at(1, 0) = -1;
  m2.at(1, 1) = -1;
  OJ_ASSERT((std::abs(m2.determinant()) - 2.0) < eps);

  m2.at(0, 0) = 1.5;
  m2.at(0, 1) = 2.5;
  m2.at(1, 0) = -2.5;
  m2.at(1, 1) = 1.5;
  OJ_ASSERT(std::abs(m2.determinant() - 8.5) < eps);

  Matrix m3(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m3.at(i, j) = i + j;
    }
  }

  OJ_ASSERT(std::abs(m3.determinant() - 0) < eps);

  m3.at(0, 0) = 2;
  m3.at(0, 1) = 9;
  m3.at(0, 2) = 4;
  m3.at(1, 0) = 7;
  m3.at(1, 1) = 5;
  m3.at(1, 2) = 3;
  m3.at(2, 0) = 6;
  m3.at(2, 1) = 1;
  m3.at(2, 2) = 8;
  OJ_ASSERT(std::abs(m3.determinant() - -360.0) < eps);

  Matrix m4(5, 5);
  m4.at(0, 0) = 1.7;
  m4.at(0, 1) = 2.4;
  m4.at(0, 2) = 0.1;
  m4.at(0, 3) = 0.8;
  m4.at(0, 4) = 1.5;
  m4.at(1, 0) = 2.3;
  m4.at(1, 1) = 0.5;
  m4.at(1, 2) = 0.7;
  m4.at(1, 3) = 1.4;
  m4.at(1, 4) = 1.6;
  m4.at(2, 0) = 0.4;
  m4.at(2, 1) = 0.6;
  m4.at(2, 2) = 1.3;
  m4.at(2, 3) = 2.0;
  m4.at(2, 4) = 2.2;
  m4.at(3, 0) = 1.0;
  m4.at(3, 1) = 1.2;
  m4.at(3, 2) = 1.9;
  m4.at(3, 3) = 2.1;
  m4.at(3, 4) = 0.3;
  m4.at(4, 0) = 1.1;
  m4.at(4, 1) = 1.8;
  m4.at(4, 2) = 2.5;
  m4.at(4, 3) = 0.2;
  m4.at(4, 4) = 0.9;
  OJ_ASSERT(std::abs(m4.determinant() - 50.7) < eps);
}

void __attribute__((optimize("O0"))) test10() {
  constexpr double eps = 1e-9;
  Matrix m1(2, 2);
  m1.at(0, 0) = -1;
  m1.at(0, 1) = 3;
  m1.at(1, 0) = 4;
  m1.at(1, 1) = 5;
  Matrix m2 = m1 + m1 * m1.transpose();
  OJ_ASSERT(m2.at(0, 0) == 9);
  OJ_ASSERT(m2.at(0, 1) == 14);
  OJ_ASSERT(m2.at(1, 0) == 15);
  OJ_ASSERT(m2.at(1, 1) == 46);

  OJ_ASSERT(std::abs(m2.trace() - 55) < eps);
  OJ_ASSERT(std::abs(m2.determinant() - 204) < eps);
}

int __attribute__((optimize("O0"))) main() {
  static_assert(
      std::is_same<decltype(std::declval<Matrix>().operator=(
                       std::declval<Matrix>())),
                   Matrix &>::value,
      "Assignment operator should return a reference to the object itself.");
  int testcase;
  std::cin >> testcase;
  switch (testcase) {
    case 1:
      test1();
      break;
    case 2:
      test2();
      break;
    case 3:
      test3();
      break;
    case 4:
      test4();
      break;
    case 5:
      test5();
      break;
    case 6:
      test6();
      break;
    case 7:
      test7();
      break;
    case 8:
      test8();
      break;
    case 9:
      test9();
      break;
    case 10:
      test10();
      break;
  }
  std::cout << testcase << std::endl;
  return 0;
}