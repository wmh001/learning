/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>

int main() {
    //  auto让编译器推算对象的类型
    auto a = 0.1;
    std::cout << a <<std::endl;
    int i = 0, &r = i;
    //  b为整数
    auto b = r;
    std::cout << b << std::endl;
    //  f为const int
    const auto f = i;
    std::cout << f << std::endl;
    i = 1;
    std::cout << f << std::endl;
    const int ci = 0, &cj = ci;
    //  decltype()代表()中表达式的返回值
    //  x类型为const int
    decltype(ci) x = 0;
    //  y类型为const int&，此时引用并非原值的同义词
    decltype(cj) y = 0;
    //  decltype(cj) z; // const int&必须初始化
    decltype(r + 0) c;  // 此时引用为原值的同义词
    // int *p = &i; // 解引用指针的返回值为引用
    //  d类型为int&
    // decltype(*p) d;
    // decltype((i)) d;  // 变量加（）返回引用
    return 0;
}
