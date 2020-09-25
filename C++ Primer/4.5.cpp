/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    //  递增递减运算符前置与后置版本
    int i = 0;
    std::cout << i++ <<std::endl;
    std::cout << i << std::endl;
    std::cout << ++i << std::endl;
    std::vector<int> v = {1, 2, 0, 9, -1, 3, -3};
    //  后置递增运算符优先级高于解引用运算符
    auto pbeg = v.begin();
    while (pbeg != v.end() && *pbeg >= 0)
        std::cout << *pbeg++ << std::endl;
    //  未定义错误
    std::string s = "hello world";
    auto beg = s.begin();
    while (beg != s.end() && !isspace(*beg))
        *beg = toupper(*beg++);
    std::cout << s << std::endl;
    return 0;
}
