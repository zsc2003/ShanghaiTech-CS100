#include <iostream>
#include <stdlib.h>

class Foo 
{
    public:
        Foo():m_value(0)
        {
            std::cout << "default constructor..." << std::endl;
        }

        Foo(int a):m_value(a)
        {
            std::cout << "constructor...with parameter " << a << std::endl; 
        }

        ~Foo()
        {
            std::cout << "destructor..." << std::endl;
        }

        Foo(const Foo& foo)
        {
            m_value = foo.m_value;
            std::cout << "copy constructor..." << std::endl;
        }

        void operator=(const Foo& foo)
        {
            m_value = foo.m_value;
            std::cout << "operator=...." << std::endl;
        }

    public:
        int m_value;

};

int main(int argc, char** argv)
{
    std::cout << "---------------" << std::endl;
    Foo foo1; // default constructor

    std::cout << "---------------" << std::endl;
    Foo foo2(2); // constructor with parameter

    std::cout << "---------------" << std::endl;
    Foo foo3 = foo2; // copy constructor
    Foo foo4(foo2);  // copy constructor

    std::cout << "---------------" << std::endl;
    Foo foo5;   // default constructor
    foo5 = foo2;   // operator=

    std::cout << foo4.m_value << std::endl;
    return 0;

}