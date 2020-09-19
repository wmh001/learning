/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
#include <vector>

int main() {
    //  ivec元素为9个8
    std::vector<int> ivec(9, 8);
    //  拷贝初始化
    std::vector<int> ivec2(ivec);
    std::vector<int> ivec3 = ivec;
    for (int i = 0; i < 9; i++) {
        std::cout << ivec[i] << ' ';
        std::cout << ivec2[i] << ' ';
        std::cout << ivec3[i] << std::endl;
    }
    //  列表初始化
    std::vector<std::string> articles{"a", "an", "the"};
    for (int i = 0; i < 3; i++) {
        std::cout << articles[i] << std::endl;
    }
    //  ivec4元素有三个，每个都默认初始化
    std::vector<int> ivec4(3);
    for (int i = 0; i < 3; i++) {
        std::cout << ivec4[i] << std::endl;
    }
    return 0;
}
