/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>

int main() {
    //  先按优先级组合，在左结合
    std::cout << (((6 + 3) * 4) / 2) + 2 << std::endl;
    std::cout << 6 + 3 * 4 / 2 + 2 << std::endl;
    //  括号无视优先级和结合律
    std::cout << (6 + 3) * (4 / 2 + 2) << std::endl;
    std::cout << ((6 + 3) * 4) / 2 + 2 <<std::endl;
    //  优先级影响程序的正确性
    int ia[] = {0, 2, 4, 6, 8};
    int last = *(ia + 4);
    std::cout << last << std::endl;
    last = *ia + 4;
    std::cout << last << std::endl;
    //  IO运算符满足左结合律
    std::cout << ia[0] << ia[1] << std::endl;
    return 0;
}
