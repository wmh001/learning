/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    //  赋值运算符左运算对象是可修改左值
    int i = 0, j = 0, k = 0;
    const int ci = 1;
    //  1024 = k;
    //  i + j = k;
    //  ci = k;
    k = 0;
    std::cout << k << std::endl;
    k = 3.14159;
    std::cout << k << std::endl;
    //  列表赋值
    std::vector<int> vi;
    vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto i : vi)
        std::cout << i << std::endl;
    //  对内置类型赋值，列表中最多只包含一个值，而且其（类型转换后）所占空间不得大于目标类型的空间
    //  k = {3.14};
    k = {true};
    std::cout << k << std::endl;
    //  列表为空时，进行值初始化
    k = {};
    std::cout << k << std::endl;
    //  赋值运算符右结合
    int iv, jv;
    iv = jv = 1;
    std::cout << iv << jv << std::endl;
    //  多重赋值语句中的每一个对象与右边对象（类型转换后）的类型相同
    std::string s1, s2;
    s1 = s2 = "OK";
    std::cout << s1 << s2 << std::endl;
    return 0;
}
