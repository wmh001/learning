# 输入正整数n，输出n行由大写字母（从A-Z重复使用）组成的三角形阵列
# 例如：输入3，输出
# A B C
# D E
# F

# 输入正整数并转换类型
n = input("请输入一个正整数:")
n = int(n)
# 获取'A'的序号
a = ord('A')
# 初始化将要输出的字符的序号与'A'的序号的差值为0
difference = 0
# 输出三角形矩阵
# i代表1~n的行号
for i in range(1, n + 1):
    # j代表将要输出的字母在第i行上的序数
    for j in range(1, n + 2 - i):
        # 输出当前字母，不换行
        print(chr(a + difference), end="")
        # 差值加1，大于26时回到'A'
        difference = (difference + 1) % 26
    # 换行
    print()
