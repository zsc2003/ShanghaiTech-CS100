#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

class Grade {
 public:
  Grade(const std::string &name, int number, double grade);
  std::string getName() const;
  void setName(const std::string &name);
  int getNumber() const;
  void setNumber(int number);
  double getGrade() const;
  void setGrade(double grade);

 private:
  std::string m_name;
  int m_number;
  double m_grade;
};

struct NameComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

struct NumberComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

struct GradeComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

class Gradesheet {
  friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet);

 public:
  Gradesheet();
  ~Gradesheet();
  std::size_t size() const;
  double average() const;
  bool addGrade(const Grade &grade);
  double findByName(const std::string &name) const;
  double findByNumber(int number) const;
  Grade &operator[](std::size_t i);
  const Grade &operator[](std::size_t i) const;
  void sortByName();
  void sortByNumber();
  void sortByGrade();

 private:
  std::vector<Grade> m_grades;
};

Grade::Grade(const std::string &name, int number, double grade)
    : m_name(name), m_number(number), m_grade(grade) {}

std::string Grade::getName() const {
  return m_name;
}

void Grade::setName(const std::string &name) {
  m_name = name;
}

int Grade::getNumber() const {
  return m_number;
}

void Grade::setNumber(int number) {
  m_number = number;
}

double Grade::getGrade() const {
  return m_grade;
}

void Grade::setGrade(double grade) {
  m_grade = grade;
}

Gradesheet::Gradesheet() {}
Gradesheet::~Gradesheet() {}

std::size_t Gradesheet::size() const {
  return m_grades.size();
}

double Gradesheet::average() const {
  double sum = 0;
  for (const Grade &grade : m_grades) {
    sum += grade.getGrade();
  }
  return sum / m_grades.size();
}

bool Gradesheet::addGrade(const Grade &grade) {
  if (findByName(grade.getName()) == -1 &&
      findByNumber(grade.getNumber()) == -1) {
    m_grades.push_back(grade);
    return true;
  } else {
    return false;
  }
}

double Gradesheet::findByNumber(int number) const {
  for (const auto &grade : m_grades) {
    if (grade.getNumber() == number) {
      return grade.getGrade();
    }
  }
  return -1;
}

double Gradesheet::findByName(const std::string &name) const {
  for (const auto &grade : m_grades) {
    if (grade.getName().compare(name) == 0) {
      return grade.getGrade();
    }
  }
  return -1;
}

Grade &Gradesheet::operator[](std::size_t i) {
  return m_grades[i];
}

const Grade &Gradesheet::operator[](std::size_t i) const {
  return m_grades[i];
}

std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet) {
  int width = 10;
  os << '/';
  for (int i = 0; i < 30; i++)
    os << '-';
  os << '\\' << std::endl;
  os << '|' << std::left << std::setw(width) << "Name" << std::setw(width)
     << "Number" << std::setw(width) << "Grade" << '|' << std::endl;
  os << '|';
  for (int i = 0; i < 30; i++)
    os << '-';
  os << '|' << std::endl;
  for (const Grade &grade : sheet.m_grades)
    os << '|' << std::left << std::setw(width) << grade.getName()
       << std::setw(width) << grade.getNumber() << std::setw(width)
       << std::setprecision(3) << grade.getGrade() << '|' << std::endl;
  os << '\\';
  for (int i = 0; i < 30; i++)
    os << '-';
  os << '/' << std::endl;
  return os;
}

void Gradesheet::sortByGrade() {
  std::sort(m_grades.begin(), m_grades.end(), GradeComparator());
}

void Gradesheet::sortByNumber() {
  std::sort(m_grades.begin(), m_grades.end(), NumberComparator());
}

void Gradesheet::sortByName() {
  std::sort(m_grades.begin(), m_grades.end(), NameComparator());
}

bool NameComparator::operator()(const Grade &a, const Grade &b) const {
  return a.getName().compare(b.getName()) < 0 ? true : false;
}

bool GradeComparator::operator()(const Grade &a, const Grade &b) const {
  return a.getGrade() > b.getGrade();
}

bool NumberComparator::operator()(const Grade &a, const Grade &b) const {
  return a.getNumber() < b.getNumber();
}