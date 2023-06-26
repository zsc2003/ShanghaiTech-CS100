#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class B;
class A {
 public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }
  void setShared(shared_ptr<B>& p) { p_ = p; }

 private:
  shared_ptr<B> p_;  // use weak_ptr instead to avoid CD
};

class B {
 public:
  B() { cout << "B()" << endl; }
  ~B() { cout << "~B()" << endl; }
  void setShared(shared_ptr<A>& p) { p_ = p; }

 private:
  shared_ptr<A> p_;
};
void cyclic() {
  shared_ptr<A> a_ptr(new A);
  shared_ptr<B> b_ptr(new B);
  a_ptr->setShared(b_ptr);
  b_ptr->setShared(a_ptr);
}
int main() {
  cyclic();
  return 0;
}