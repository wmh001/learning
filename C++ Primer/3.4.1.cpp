/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
#include <vector>

int main() {
    std::string s("some string");
    //  迭代器的begin指向第一个元素，end指向最后一个元素的下一个位置
    //  如果被指对象是常量则返回const_iterator类型，否则返回iterator类型
    if (s.begin() != s.end()) {
        auto it = s.begin();
        *it = toupper(*it);
    }
    for (auto i : s)
        std::cout << i;
    std::cout << std::endl;
    //  isspace函数用于判断是否为空格
    for (auto it = s.begin(); it != s.end()  && !isspace(*it) ; ++it) {
        *it = toupper(*it);
    }

    for (auto i : s)
        std::cout << i;
    std::cout << std::endl;
    //  迭代器类型
    //  it可读可写
    std::vector<int>::iterator it;
    //  it2可读可写
    std::string::iterator it2;
    //  it3相当于常量指针，可读不可写
    std::vector<int>::const_iterator it3;
    //  it4可读不可写
    std::string::const_iterator it4;
    //  cbegin()只返回const_iterator类型
    auto it5 = s.cbegin();
    std::cout << *it5 << std::endl;
    std::vector<std::string> text = {"I have an appale.", "", "I have a pen."};
    for (auto it6 = text.cbegin();
        //  empty()成员判断元素是否为空
        //  ->是解引用与访问成员的结合
        it6 != text.cend() && !it6 -> empty(); ++it6) {
        std::cout << *it6 << std::endl;
    }
    //  任何可能改变vector对象容量的操作都会使迭代器失效
    return 0;
}

