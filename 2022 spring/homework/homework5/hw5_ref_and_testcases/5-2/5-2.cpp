#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>

const double PI = 3.14159;

// As is said in the problem description, the 'Shape' class should be an
// abstract class. So at least one of the member functions should be pure
// virtual. A possible implementation is as follows. You can also declare
// 'NumberCorners' to be pure virtual, and override it in the subclasses.

// Note: You should NEVER declare a impure virtual function without defining it.
// This will make the compiler fail to generate the virtual-table (named
// 'vptr' or 'vtable' or sometimes 'typeinfo'), which is crucial to performing
// dynamic binding.
class Shape {
 public:
  Shape(int numberCorners);

  // A polymorphic class MUST have a virtual destructor.

  // When a pointer to the base class is passed to 'delete', dynamic binding
  // will be performed and the correct destructor will be called according to
  // the real type of the object that pointer is pointing to.

  // For example:
  //    Shape *p = new Square(3);
  //    delete p;   // will call Square::~Square, not Shape::~Shape.
  virtual ~Shape() {}

  virtual double CalculateArea() const = 0;
  virtual double CalculatePerimeter() const = 0;
  int NumberCorners() const;

 private:
  int m_numberCorners;
};

Shape::Shape(int numberCorners) : m_numberCorners(numberCorners) {}

int Shape::NumberCorners() const {
  return m_numberCorners;
}

class Square : public Shape {
 public:
  Square(double length);
  virtual ~Square() {
    std::cout << "A Square has been destroyed." << std::endl;
  }

 protected:
  double m_length;

  virtual double CalculateArea() const override;
  virtual double CalculatePerimeter() const override;
};

Square::Square(double length) : Shape(4), m_length(length) {}

double Square::CalculateArea() const {
  return m_length * m_length;
}

double Square::CalculatePerimeter() const {
  return 4.0 * m_length;
}

class Rectangle : public Shape {
 public:
  Rectangle(double shortSide, double longSide);
  virtual ~Rectangle() {
    std::cout << "A Rectangle has been destroyed." << std::endl;
  }

 protected:
  double m_shortSide;
  double m_longSide;

  virtual double CalculateArea() const override;
  virtual double CalculatePerimeter() const override;
};

Rectangle::Rectangle(double shortSide, double longSide)
    : Shape(4), m_shortSide(shortSide), m_longSide(longSide) {}

double Rectangle::CalculateArea() const {
  return m_shortSide * m_longSide;
}

double Rectangle::CalculatePerimeter() const {
  return 2.0 * (m_shortSide + m_longSide);
}

class Triangle : public Shape {
 public:
  Triangle(double shortSide, double longSide);
  virtual ~Triangle() {
    std::cout << "A Triangle has been destroyed." << std::endl;
  }

 protected:
  double m_shortSide;
  double m_longSide;

  virtual double CalculateArea() const override;
  virtual double CalculatePerimeter() const override;
};

Triangle::Triangle(double shortSide, double longSide)
    : Shape(3), m_shortSide(shortSide), m_longSide(longSide) {}

double Triangle::CalculateArea() const {
  return 0.5 * (m_shortSide * m_longSide);
}

double Triangle::CalculatePerimeter() const {
  return m_shortSide + m_longSide +
         sqrt(m_shortSide * m_shortSide + m_longSide * m_longSide);
}

class Circle : public Shape {
 public:
  Circle(double radius);
  virtual ~Circle() {
    std::cout << "A Circle has been destroyed." << std::endl;
  }

 protected:
  double m_radius;

  virtual double CalculateArea() const override;
  virtual double CalculatePerimeter() const override;
};

Circle::Circle(double radius) : Shape(0), m_radius(radius) {}

double Circle::CalculateArea() const {
  return PI * m_radius * m_radius;
}

double Circle::CalculatePerimeter() const {
  return 2.0 * PI * m_radius;
}

static_assert(std::is_abstract<Shape>::value,
              "'Shape' should be an abstract base class!");

int main() {
  // initialize an empty list of shapes
  std::list<Shape *> shapeDatabase;
  // interact with the user: ask the user to enter shapes one by one
  while (1) {
    // print instructions as to how to enter a shape
    std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
    std::cout << "and one or two size parameters, ";
    std::cout << "separated with blank spaces:\n";
    double size1;
    double size2;
    // check which shape has been requested and store in the database
    std::string shapeType;
    std::cin >> shapeType;
    if (shapeType == std::string("Circle")) {
      std::cin >> size1;
      shapeDatabase.push_back(new Circle(size1));
    } else if (shapeType == std::string("Triangle")) {
      std::cin >> size1 >> size2;
      shapeDatabase.push_back(new Triangle(size1, size2));
    } else if (shapeType == std::string("Square")) {
      std::cin >> size1;
      shapeDatabase.push_back(new Square(size1));
    } else if (shapeType == std::string("Rectangle")) {
      std::cin >> size1 >> size2;
      shapeDatabase.push_back(new Rectangle(size1, size2));
    } else {
      std::cout << "Unrecognized shape!!\n";
    }
    // check if the user wants to add more shapes
    std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
    std::string answer;
    std::cin >> answer;
    if (answer != std::string("Y"))
      break;
  }
  // iterate through the list and output the area, perimeter,
  // and number of corners of each entered shape
  std::list<Shape *>::iterator it = shapeDatabase.begin();
  int shapeCounter = 0;
  while (it != shapeDatabase.end()) {
    std::cout << "Properties of shape " << shapeCounter++ << ":\n";
    std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea()
              << "\n";
    std::cout << "Perimeter: " << std::setprecision(5)
              << (*it)->CalculatePerimeter() << "\n";
    std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
    std::cout << std::endl;
    it++;
  }

  it = shapeDatabase.begin();
  while (it != shapeDatabase.end()) {
    delete (*it);
    it = shapeDatabase.erase(it);
  }

  return 0;
}