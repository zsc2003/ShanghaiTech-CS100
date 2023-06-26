#include <iostream>
#include <stdlib.h>

class Foo 
{
    public:
        Foo():m_value(0)
        {
            std::cout << "default constructor of Foo... " << std::endl;
        }

        Foo(int a):m_value(a)
        {
            std::cout << "constructor of Foo...with parameter " << a << std::endl; 
        }

        ~Foo()
        {
            std::cout << "destructor of Foo..." << std::endl;
        }

        Foo(const Foo& foo)
        {
            std::cout << "copy constructor of Foo..." << std::endl;
        }

        Foo& operator=(const Foo& foo)
        {
            m_value = foo.m_value;
            std::cout << "operator= of Foo.... " << std::endl;
            return *this;
        }

    public:
        int m_value;
};

class Bar
{
public:
    Bar()
    {
        std::cout << "default constructor of Bar..." << std::endl;
    };

    Bar(Foo &foo):m_foo(foo)
    {
        // m_foo = foo; // try to de-comment this line and delete the initializer-list
        std::cout << "constructor of Bar ... with parameter" << std::endl;
    }
    ~Bar()
    {
        std::cout << "destructor of Bar..." << std::endl;
    };

public:
    Foo m_foo;
};

int main (int argc, char **argv)
{
    std::cout << "---------------" << std::endl;
    Foo foo1(2);

    std::cout << "---------------" << std::endl;
    Bar bar1(foo1);
    return 0;
}