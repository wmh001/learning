/*
#Copyright 2020 BingchunFeng. All rights reserved
*/
#include <iostream>
using namespace std;

int main() {
    string str = "Hello";
    string phrase = "Hello world";
    string slang = "Hiya";
    string str2 = "World", str3;
    //  字符串比较按字典顺序
    if (str < phrase)
        cout << "True" << endl;
    if (str < slang)
        cout << "True" << endl;
    //  字符串相加为串接
    str3 = str + ", " + str2 + "!\n";
    cout << str3;
    return 0;
}
