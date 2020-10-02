/*
#Copyright[2020]<Wang Maohua>
*/

#include <iostream>
using namespace std;

int main() {
    //  默认初始化
    string s1;
    //  s2是s1的副本
    string s2 = s1;
    //  拷贝初始化，s3是字符串字面值的副本
    string s3 = "hiya";
    //  拷贝初始化，连续相同字符初始化
    string s4(10, 'c');
    string s5 = string(10, 'c');
    string s6, s7, s8;
    cout << s1 << endl;
    cin >> s2;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    cin >> s6 >> s7;
    cout << s6 << endl;
    cout << s7 << endl;
    //  getline()读入一整行
    while (getline(cin, s8))
        //  size()成员函数返回字符串长度
        if (s8.size() > 8)
            cout << s8 << endl;
    return 0;
}
