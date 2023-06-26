

4.++p是左值，p++是右值![1681738129419](C:\Users\13540\AppData\Roaming\Typora\typora-user-images\1681738129419.png)

![1681738139844](C:\Users\13540\AppData\Roaming\Typora\typora-user-images\1681738139844.png)

5.cin不是function

7.s2 cppreference上没有这个初始化方式-> warning

​	s4 48个1

8.'+' 跟随前面的类型

10.B:引用的目的: 更改，减少不必要的拷贝构造

E. 函数返回值类型少了个const

F.第一题: const char [5]

11.B new 会调用构造函数，malloc不会

12.print_array_cpp 传入的是一个长度为10 的数组，而print_array_c的参数会退化成为int*类型的指针

14.signed int=int,

​	int [10] 退化成int*

15.b是a的reference

​	b,d都是a的引用=>int* c指向的是a

16.有同学反应说>>会报错，较早的编译器确实会这样，但新的编译器已经优化了

17.顶层const和底层const的问题

19.C里面NULL就是0

​	c++ standard规定只能是最普通的0，计算出来的0都是不可以的



  std::move() 函数将一个左值强制转化为右值引用，以用于移动语义。

移动语义，允许直接转移对象的资产和属性的所有权，而在参数为右值时无需复制它们。

换一种说法就是，std::move() 将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。

因此，通过std::move()，可以避免不必要的拷贝操作。  

![img](file:///D:\1354038619\Image\C2C\F69192023CCD2E95893493AC5089FC55.jpg)