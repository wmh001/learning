/*
#Copyright 2020 BingchunFeng. All rights reserved
*/
#include <iostream>

int main() {
    int max;
    std::cin >> max;
    //  const声明的对象的具体值可能在运行过程中得到
    const int Max = max;
    std::cout << Max;
    //  constexpr声明的对象一定是常量且被常量表达式初始化
    constexpr int MAX = 20 - 1;
    std::cout << MAX;
}
