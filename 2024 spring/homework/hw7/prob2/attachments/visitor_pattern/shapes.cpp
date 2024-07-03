#include <iostream>
#include <memory>
#include <vector>

class ShapeVisitor;

class Shape {
  double mBaseX;
  double mBaseY;

public:
  Shape(double baseX, double baseY) : mBaseX{baseX}, mBaseY{baseY} {}

  double getBaseX() const { return mBaseX; }
  double getBaseY() const { return mBaseY; }

  virtual void accept(ShapeVisitor &visitor) = 0;

  virtual ~Shape() = default;
};

class Circle;
class Rectangle;

class ShapeVisitor {
public:
  virtual void visit(Circle &) = 0;
  virtual void visit(Rectangle &) = 0;
  virtual ~ShapeVisitor() = default;
};

class Circle : public Shape {
  double mRadius;

public:
  Circle(double centerX, double centerY, double radius)
      : Shape{centerX, centerY}, mRadius{radius} {}

  double getRadius() const { return mRadius; }

  void accept(ShapeVisitor &visitor) override { visitor.visit(*this); }
};

class Rectangle : public Shape {
  double mHeight;
  double mWidth;

public:
  Rectangle(double topLeftX, double topLeftY, double height, double width)
      : Shape{topLeftX, topLeftY}, mHeight{height}, mWidth{width} {}

  double getHeight() const { return mHeight; }
  double getWidth() const { return mWidth; }

  void accept(ShapeVisitor &visitor) override { visitor.visit(*this); }
};

class PrintInfoVisitor : public ShapeVisitor {
  std::ostream &mOS;

public:
  explicit PrintInfoVisitor(std::ostream &os = std::cout) : mOS{os} {}

  void visit(Circle &c) override {
    mOS << "Circle centered at (" << c.getBaseX() << ", " << c.getBaseY()
        << "), with radius " << c.getRadius() << '\n';
  }

  void visit(Rectangle &r) override {
    mOS << "Rectangle with top-left vertex at (" << r.getBaseX() << ", "
        << r.getBaseY() << "), height " << r.getHeight() << " and width "
        << r.getWidth() << '\n';
  }
};

class ComputeAreaVisitor : public ShapeVisitor {
  double mResult;

  static constexpr double Pi = 3.14159265;

public:
  void visit(Circle &c) override {
    mResult = Pi * c.getRadius() * c.getRadius();
  }

  void visit(Rectangle &r) override { mResult = r.getHeight() * r.getWidth(); }

  double getResult() const { return mResult; }
};

void printInfo(const std::vector<std::unique_ptr<Shape>> &shapes) {
  PrintInfoVisitor visitor{std::cout};
  for (const auto &pShape : shapes)
    pShape->accept(visitor);
}

double computeTotalArea(const std::vector<std::unique_ptr<Shape>> &shapes) {
  double sum = 0;
  ComputeAreaVisitor visitor;
  for (const auto &pShape : shapes) {
    pShape->accept(visitor);
    sum += visitor.getResult();
  }
  return sum;
}

int main() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Rectangle>(1, 2, 3, 4));
  shapes.push_back(std::make_unique<Circle>(5, 6, 7));
  shapes.push_back(std::make_unique<Rectangle>(1, 2, 1, 5));
  printInfo(shapes);
  std::cout << "Total area: " << computeTotalArea(shapes) << '\n';
  return 0;
}