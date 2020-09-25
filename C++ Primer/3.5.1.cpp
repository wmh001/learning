/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>

int main() {
    //  数组规模必须是正值的常量表达式，定义数组时必须指明类型，不能用auto
    /* unsigned cnt = 42;
    int bad[cnt];
    for (int i = 0; i < 42; i++) {
        std::cout << bad[i];
    }
    std::cout << std::endl;*/
    //  列表初始化
    const unsigned siz = 3;
    int ial[siz] = {0, 1, 2};
    //  数组规模省略
    int ial2[] = {0, 1, 2};
    //  初始化前部，默认初始化后部，此时初始值数量不可超过数组规模
    int ial3[5] = {0, 1, 2};
    std::string ial4[3] = {"hi", "bye"};
    for (int i = 0; i < siz; i++) {
        std::cout << ial[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << ial2[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << ial[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << ial4[i];
    }
    std::cout << std::endl;

    //  字符数组初始化需考虑为空字符串留空间
    //  隐式
    char a1[] = {'c', '+', '+'};
    //  显式
    char a2[] = {'c', '+', '+', '\0'};
    //  自动
    char a3[] = "c++";
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;
    //  溢出
    //  const char a4[6] = "Daniel";
    //  不能将数组拷贝给另一数组
    //  char a4[] = a;
    //  定义一个数组指针
    int a = 1, b = 2, c = 3;
    int *ptrs[3] = {&a, &b, &c};
    //  不能定义引用数组
    //  int &ptrs[10];
    //  定义指向含十个整数的数组的指针
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int (*Parray)[10] = &arr;
    for (int i = 0; i < 10; i++) {
        std::cout << (*Parray)[i];
    }
    std::cout << std::endl;
    //  定义含十个整数数组的引用
    int (&arrRef)[10] = arr;
    for (int i = 0; i < 10; i++) {
        std::cout << arrRef[i];
    }
    std::cout << std::endl;
    //  定义数组的引用，数组含三个指向int的指针
    int *(&array)[3] = ptrs;
    for (int i = 0; i < 3; i++) {
        std::cout << *(array[i]);
    }
    std::cout << std::endl;
    return 0;
}
