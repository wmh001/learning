/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>

int main() {
    std::string str("some string");
    std::string s("Hello World!!!");
    decltype(s.size()) punct_cut = 0;
    const std::string hexdigits = "0123456789ABCDEF";
    std::string result;
    std::string::size_type n;
    //  范围for语句
    for (auto c : str)
        std::cout << c << std::endl;
    //  统计字符串中标点符号的个数
    for (auto c : s)
        if (ispunct(c))
            ++punct_cut;
    std::cout << punct_cut << " punctuation characters in " << s << std::endl;
    //  将字符串的每个字目变为大写
    for (auto &c : s)
        c = toupper(c);
    std::cout << s << std::endl;
    //  将字符串的首字母大写
    if (!str.empty())
        str[0] = toupper(str[0]);
    std::cout << str << std::endl;
    //  将字符串的第一个单词大写
    for (decltype(str.size()) index = 0;
        index != str.size() && !isspace(str[index]);
        ++index)
        str[index] = toupper(str[index]);
    std::cout << str << std::endl;
    //  10进制与16进制转换
    while (std::cin >> n)
        if (n < hexdigits.size())
            result += hexdigits[n];
    std::cout << "Your hex number is: " << result << std::endl;
    return 0;
}
