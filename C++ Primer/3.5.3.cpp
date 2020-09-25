/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>

int main() {
    std::string nums[] = {"one", "two", "three"};
    // p指向nums的第一个元素
    //  std::string *p = &nums[0];
    std::string *p = nums;
    std::cout << *p << std::endl;
    //  数组的auto推断类型为指针
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //  auto ia2("&"ia[0]);
    auto ia2(ia);
    for (int i = 0; i < 10; i++)
        std::cout << ia2[i] << std::endl;
    //  decltype的返回类型为同元素数量的数组
    decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto a : ia3)
        std::cout << a << std::endl;
    //  指向数组元素的指针也是迭代器，支持迭代器的运算
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *e = &arr[10];
    for (int *b = arr; b != e; ++b)
        std::cout << *b;
    std::cout << std::endl;
    std::cout << *(e - 4) << std::endl;
    //  begin与end
    int *beg = std::begin(arr);
    int *last = std::end(arr);
    for (; beg != last; ++beg)
        std::cout << *beg;
    std::cout << std::endl;
    //  指向数组元素的指针差为ptrdiff_t类型，可为负值
    auto a = std::end(arr) - std::begin(arr);
    std::cout << a << std::endl;
    //  指向同一数组元素的指针比较
    if (beg == last)
        std::cout << "True" << std::endl;
    //  下标运算
    int *m = &ia[2];
    int n = m[-1];
    std::cout << n << std::endl;
    return 0;
}
