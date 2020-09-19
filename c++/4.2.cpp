/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>

int main() {
    //  一元负号作用于算术值返回相反数（提升后）右值
    int i = 1024;
    int k = -i;
    std::cout << i << " " << k << std::endl;
    //  一元负号作用于布尔值，真返回1，假返回0
    bool b = true;
    bool d = -b;
    std::cout << b << " " << d << std::endl;
    bool a = false;
    bool c = -a;
    std::cout << a << " " << c << std::endl;
    //  溢出
    short sv = 32767;
    sv += 1;
    std::cout << sv << std::endl;
    //  整数相除结果为整数
    std::cout << 21 / 6 << std::endl;
    float val = 21 / 6;
    std::cout << val << std::endl;
    val = 21.0 / 6.0;
    std::cout << val << std::endl;
    //  取余运算对象必须为整数
    int ival = 42;
    double dval = 3.14;
    std::cout << ival % 12 << std::endl;
    //  std::cout << ival % dval << std::endl;
    //  m = m / n * n +m % n
    std::cout << ival / 12 * 12 << std::endl;
    std::cout << ival / 12 * 12 + ival % 12 << std::endl;
    //  -(m/n)=(-m)/n=m/(-n)
    std::cout << -(42 / 12) << " " << (-42) / 12 << " " << 42 / (-12) <<
    std::endl;
    //  m % (-n) = m % n,(-m) % n = -(m % n)
    std::cout << 42 % 12 << " " << 42 % (-12) << std::endl;
    std::cout << (-42) % 12 << " " << -(42 % 12) << std::endl;
    return 0;
}
