/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v2;
    for (int i = 0; i != 10; i++) {
        //  push_back()成员向vector对象添加元素，不能用下标添加元素
        v2.push_back(i);
    }
    for (int i = 0; i != 10; i++) {
        std::cout << v2[i] << std::endl;
    }

    std::string word;
    std::vector<std::string> text;
    while (std::cin >> word) {
        text.push_back(word);
    }
    //  empty()成员检验是否为空
    std::cout << text.empty() << std::endl;
    //  size()成员返回元素个数
    std::cout << text.size() << std::endl;
    return 0;
}
