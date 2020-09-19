/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
#include <cstring>
#include <vector>

int main() {
    //  c风格字符串
    //  以空字符为结尾
    char ca[] = {'c', '+', '+', '\0'};
    std::cout << strlen(ca) << std::endl;
    //  比较字符串
    //  直接用<、>等比较的是指针
    //  前面大于后面返回正值，相等返回0，小于返回负值
    const char s1[] = "A string example";
    const char s2[] = "A different string";
    if (strcmp(s1, s2) < 0)
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
    char s[40];
    strcpy(s, s1);
    strcat(s, " ");
    strcat(s, s2);
    std::cout << s <<std::endl;
    std::string s3 = "c++";
    //  旧风格代码接口，调用后s3的值改变可能导致字符数组失效
    const char *s4 = s3.c_str();
    std::cout << s4[0] << std::endl;
    //  用数组初始化vector
    int int_arr[] = {0, 1, 2, 3, 4, 5};
    std::vector<int> ivec(std::begin(int_arr), std::end(int_arr));
    for (auto a : ivec)
        std::cout << a << std::endl;
    std::vector<int> ivec2(int_arr + 1, int_arr + 4);
    for (auto a : ivec2)
        std::cout << a << std::endl;
    return 0;
}
