/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
#include <vector>

int main() {
    /*std::string word;
    std::vector<std::string> text;
    while (std::cin >> word) {
        text.push_back(word);
    }
    std::cout << text.empty() << std::endl;
    std::cout << text.size() << std::endl;*/

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    //  对vector的每一个元素平方
    for (auto &i : v)
        i *= i;
    for (auto i : v)
        std::cout << i << " ";
    std::cout << std::endl;
    int a[14] = {42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93};
    std::vector<unsigned> scores(11, 0);
    //  计算索引
    for (int i = 0; i < 14; i++) {
        if (a[i] <= 100)
            ++scores[a[i] / 10];
    }
    for (auto i : scores)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
