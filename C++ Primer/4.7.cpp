/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
#include <string>

int main() {
    int grade;
    std::cin >> grade;
    //  条件表达式
    std::string finalgrade = (grade < 60) ? "fail" : "pass";
    std::cout << finalgrade << std::endl;
    //  嵌套条件表达式
    finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass";
    std::cout << finalgrade << std::endl;
    //  在输出运算符中使用条件运算符
    //  条件运算符的优先级非常低
    std::cout << ((grade < 60) ? "fail" : "pass") <<  std::endl;
    //  输出grade < 60的结果
    //  cout << (grade < 60);
    //  cout ? "fail" : "pass";
    std::cout << (grade < 60) ? "fail" : "pass";
    std::cout << std::endl;
    //  cout << grade;
    //  cout < 60 ? "fail" : "pass";
    //  std::cout << grade < 60 ? "fail" : "pass";
    return 0;
}
