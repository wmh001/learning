/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
#include <string>

int main() {
    //   成员访问运算符
    std::string s1 = "a string", *p = &s1;
    auto n = s1.size();
    std::cout << n << std::endl;
    //  ptr->mem <==> (*ptr).mem
    n = (*p).size();
    std::cout << n << std::endl;
    n = p->size();
    std::cout << n << std::endl;
    return 0;
}
