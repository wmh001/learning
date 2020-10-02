/*
#Copyright[2020]<Wang Maohua>
*/

//  迭代器支持的运算：+n、-n、+=n、-=n、-、>、>=、<、<=
#include <iostream>
#include <vector>

int main() {
    std::string s("some string");
    // +n
    auto mid = s.begin() + s.size()/2;
    auto begin = s.begin();
    std::cout << *mid << std::endl;
    //  <
    if (begin < mid) {
        std::cout << "True" << std::endl;
    }
    //  -，返回值为difference_type，可正可负
    std::cout << mid - begin << std::endl;
    //  二分搜索
    /* auto beg = s.begin(), end = s.end();
    auto mid = s.begin() + (end - beg) / 2;
    while (mid != end && *mid != sought) {
        if (sought < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }*/
    return 0;
}
