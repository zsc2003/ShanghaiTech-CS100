#include <iostream>
#include <stdlib.h>

class Foo 
{
    public:
        Foo()
        {
            m_ptr = new int(0);
            std::cout << "default constructor of Foo... " << std::endl;
        }

        Foo(int a)
        {
            m_ptr = new int(a);
            std::cout << "constructor of Foo...with parameter " << a << std::endl; 
        }

        ~Foo()
        {
            delete m_ptr;
            m_ptr = nullptr;
            std::cout << "destructor of Foo..." << std::endl;
        }

        // Foo(const Foo& foo)
        // {
        //     m_ptr = new int(*foo.m_ptr);
        //     std::cout << "copy constructor of Foo..." << std::endl;
        // }

        // void operator=(const Foo& foo)
        // {
        //     *m_ptr = *foo.m_ptr;
        //     std::cout << "operator= of Foo.... " << std::endl;
        // }

    public:
        int* m_ptr;
};

void f(Foo& foo)
{
    Foo temp = foo;
    return;
}

int main(int argc, char** argv)
{
    Foo foo1(2);
    f(foo1);

    // double free, beacause the m_ptr has been freed in the function
    // try to de-comment the code above to make it right
    // this may not cause segmentation fault in Windows which I dont know why
    // But this will definitely crash in linux system
    return 0;
}