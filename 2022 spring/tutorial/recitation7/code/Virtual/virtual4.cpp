#include<string>
#include<iostream>
using namespace std;

class Base {
public:
    Base(const string& ss) { 
        cout << "Base constructor\n"; 
        f(ss); 
    }
    virtual void f(const string&) { 
        cout << "Base::f\n";
    }
};

class Derived : public Base {
public:
    Derived(const string & ss) :Base(ss) { 
        cout << "Derived constructor\n";
    }
    void f(const string& ss) { 
        cout << "Derived::f\n"; 
        s = ss;
    }
private:
    string s;
};

int main(){
    // Use virtual functions in constructor
    Derived d("Hello");
    Base e("Hello");
    return 0;
}
