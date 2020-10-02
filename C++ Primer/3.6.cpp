/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
//  多维数组
int main() {
    //  多维数组即为数组的数组
    //  初始化
    //  缺省初始化
    int ia[3][4] = {0};
    for (int i = 0; i < 3; i++)
        for (auto b : ia[i])
            std::cout << b;
    std::cout <<std::endl;
    //  只初始化每行第一个元素、
    int ia1[3][4] = {{0}, {4}, {8}};
    for (int i = 0; i < 3; i++)
        for (auto b : ia1[i])
            std::cout << b;
    std::cout <<std::endl;
    //  只初始化一行
    int ix[3][4] = {0, 1, 2, 3};
    for (int i = 0; i < 3; i++)
        for (auto b : ix[i])
            std::cout << b;
    std::cout <<std::endl;
    //  全体初始化
    int ia2[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}
        };
    for (int i = 0; i < 3; i++)
        for (auto b : ia2[i])
            std::cout << b;
    std::cout <<std::endl;
    int ia3[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 3; i++)
        for (auto b : ia3[i])
            std::cout << b;
    std::cout <<std::endl;
    //  引用
    //  row数组含ia[1][0]、ia[1][1]、ia[1][2]、ia[1][3]
    int (&row)[4] = ia3[1];
    for (auto a : row)
        std::cout << a;
    std::cout << std::endl;
    //  嵌套处理
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia4[rowCnt][colCnt] = {0};
    for (size_t i = 0; i != rowCnt; i++)
        for (size_t j = 0; j != colCnt; j++)
            ia4[i][j] = i * colCnt + j;
    for (int i = 0; i < 3; i++)
        for (auto b : ia4[i])
            std::cout << b;
    std::cout <<std::endl;
    //  范围for循环处理
    int ia5[3][4] = {0};
    size_t cnt = 0;
    for (auto &row : ia5)
        for (auto &col : row) {
            col = cnt;
            ++cnt;
        }
    for (int i = 0; i < 3; i++)
        for (auto b : ia5[i])
            std::cout << b;
    std::cout <<std::endl;
    for (auto &row : ia5)
        for (auto a : row)
            std::cout << a;
    std::cout << std::endl;
    //  多维数组名指向首元素
    int (*p)[4] = ia5;
    for (auto a : *p)
        std::cout << a;
    std::cout << std::endl;
    p = &ia5[2];
    for (auto a : *p)
        std::cout << a;
    std::cout << std::endl;
    for (int (*q)[4] = ia5; q != ia5 +3; ++q)
        for (int *m = *q; m != *q + 4; ++m)
            std::cout << *m;
    std::cout << std::endl;
    //  begin()与end()
    for (int (*s)[4] = std::begin(ia5); s != std::end(ia5); s++)
        for (int* t = std::begin(*s); t != std::end(*s); t++)
            std::cout << *t;
    std::cout << std::endl;
    //  类型别名
    using int_array = int[4];
    //  typedef int int_array[4];
    for (int_array *p = ia5; p != ia5 +3; ++p)
        for (int *q = *p; q != *p + 4; ++q)
            std::cout << *q;
    std::cout << std::endl;
    return 0;
}
