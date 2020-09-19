/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>

int main() {
    //  同一表达式两个子表达式修改了同一对象，未定义求值顺序，可能产生错误
    int i = 0;
    std::cout << i << " " << ++i << std::endl;
    return 0;
}
