/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
int main() {
    int errNumb = 0;
    //  常量指针，指向的地址不变
    int *const curErr = &errNumb;
    //  常量对象
    const double pi = 3.1415926;
    //  指向常量对象的常量指针
    const double *const pip = &pi;
    //  *pip = 2.72;
    //  常量指针指向的对象的值可重置
    *curErr = 1;
    std::cout << errNumb << std::endl;
    std::cout << *curErr << std::endl;
    std::cout << pi << std::endl;
    std::cout << *pip << std::endl;
    return 0;
}
