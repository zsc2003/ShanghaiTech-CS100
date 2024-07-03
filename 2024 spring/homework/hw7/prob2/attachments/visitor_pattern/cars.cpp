#include <iostream>
#include <memory>
#include <string>
#include <vector>

class CarElementVisitor;

class CarElement {
public:
  virtual void accept(CarElementVisitor &visitor) = 0;
  virtual ~CarElement() = default;
};

class Body;
class Car;
class Engine;
class Wheel;

class CarElementVisitor {
public:
  virtual void visit(Body &body) = 0;
  virtual void visit(Car &car) = 0;
  virtual void visit(Engine &engine) = 0;
  virtual void visit(Wheel &wheel) = 0;
  virtual ~CarElementVisitor() = default;
};

class Wheel : public CarElement {
  std::string mName;

public:
  explicit Wheel(std::string name) : mName{std::move(name)} {}

  const std::string &getName() const { return mName; }

  void accept(CarElementVisitor &visitor) override { visitor.visit(*this); }
};

class Body : public CarElement {
public:
  void accept(CarElementVisitor &visitor) override { visitor.visit(*this); }
};

class Engine : public CarElement {
public:
  void accept(CarElementVisitor &visitor) override { visitor.visit(*this); }
};

class Car : public CarElement {
  std::vector<std::unique_ptr<CarElement>> mElements;

public:
  Car() {
    // Note: We cannot list-initialize mElements because std::unique_ptr is not
    // copyable.
    mElements.push_back(std::make_unique<Wheel>("front left"));
    mElements.push_back(std::make_unique<Wheel>("front right"));
    mElements.push_back(std::make_unique<Wheel>("back left"));
    mElements.push_back(std::make_unique<Wheel>("back right"));
    mElements.push_back(std::make_unique<Body>());
    mElements.push_back(std::make_unique<Engine>());
  }

  void accept(CarElementVisitor &visitor) override {
    for (const auto &element : mElements)
      element->accept(visitor);
    visitor.visit(*this);
  }
};

class CarElementDoVisitor : public CarElementVisitor {
public:
  void visit(Body &) override { std::cout << "Moving my body" << '\n'; }

  void visit(Car &) override { std::cout << "Starting my car" << '\n'; }

  void visit(Wheel &wheel) override {
    std::cout << "Kicking my " << wheel.getName() << " wheel" << '\n';
  }

  void visit(Engine &) override { std::cout << "Starting my engine" << '\n'; }
};

class CarElementPrintVisitor : public CarElementVisitor {
public:
  void visit(Body &) override { std::cout << "Visiting body" << '\n'; }

  void visit(Car &) override { std::cout << "Visiting car" << '\n'; }

  void visit(Engine &) override { std::cout << "Visiting engine" << '\n'; }

  void visit(Wheel &wheel) override {
    std::cout << "Visiting " << wheel.getName() << " wheel" << '\n';
  }
};

int main() {
  Car car;

  CarElementPrintVisitor printer;
  car.accept(printer);

  CarElementDoVisitor doer;
  car.accept(doer);

  return 0;
}