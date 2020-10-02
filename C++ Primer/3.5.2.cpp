/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>

int main() {
    //  通过下标访问数组元素
    unsigned scores[11] = {};
    unsigned grade;
    for (int i = 0; i < 14; i++) {
        std::cin >> grade;
        ++scores[grade/10];
    }

    for (auto a : scores) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
    return 0;
}

