/*
#Copyright 2020 BingchunFeng. All rights reserved
*/

#include <iostream>
#include <vector>

int main() {
    std::string s0 = "Hello world, Hello C++,";
    std::string s1 = "Hello python, Hello JAVA.";
    std::string s2 = "";
    std::string s3 = "Hello linux. Hello arduino.";
    std::vector<std::string> text;
    text.push_back(s0);
    text.push_back(s1);
    text.push_back(s2);
    text.push_back(s3);
    for (const auto &a : text) {
        std::cout << a;
        //  左侧满足时，才进行右侧计算，保证了安全性
        //  遇到空字符串或者以句号结尾的字符串进行换行
        if (a.empty() || a[a.size() - 1] == '.')
            std::cout << std::endl;
        else
            std::cout << " ";
    }
    //  容器不空输出
    if (!text.empty())
        std::cout << text[0] << std::endl;
    //  关系运算符连写在一起从左向右计算，真为1，假为0
    if (1 < 2 < 2)
        std::cout << "True" << std::endl;
    //  布尔值作为关系运算符的运算对象时真为1，假为0
    if (1 == true)
        std::cout << "true" << std::endl;
    return 0;
}
