/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
int main() {
    //  typedef用于定义类型别名
    typedef double wages;  //  wages是double的别名
    typedef wages base, *p;
    //  using用于声明类别别名
    using base = double;
    using p = base*;
    base pi = 3.1415926;
    p pip = &pi;
    std::cout << pi << std::endl;
    std::cout << *pip << std::endl;
}
