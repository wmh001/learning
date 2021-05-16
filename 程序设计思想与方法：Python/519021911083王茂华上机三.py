# 输入一个三位数n，
# 找出100～n之间所有满足如下条件的数x：
# x是完全平方数并且x有两位数字相同，如144，676等。
# 输出这样的x，并统计个数。

from math import sqrt


# 获取输入的数
def getinput():
    # 输入三位数并转换类型
    n = input("请输入一个大于100的三位数：")
    n = int(n)
    # 如果输入非法，重新输入
    while n < 100 or n > 999:
        print("输入非法，请重新输入！")
        n = input("请输入一个大于100的三位数：")
        n = int(n)
    return n


# 判断x是否为完全平方数
def isPerfact(x):
    # 对x开平方
    square_root = sqrt(x)
    # 取整
    square_root = int(square_root)
    # 取整后再平方的结果等于x则是完全平方数
    if x == square_root ** 2:
        return True
    else:
        return False


# 是否有两个数位的数字相同
def isSame(x):
    # 取个位
    digit2 = x % 10
    # 取十位
    digit1 = int(x / 10) % 10
    # 取百位
    digit0 = int(x / 100)
    # 三位数字都不同
    if digit0 != digit1 and digit0 != digit2 and digit1 != digit2:
        return False
    # 三位数字都相同
    elif digit0 == digit2 and digit1 == digit2:
        return False
    else:
        return True


def main():
    # 获取输入
    n = getinput()
    # 初始化变量以统计个数
    count = 0
    # 100到n遍历
    for i in range(100, n + 1):
        # 如果满足条件，输出并个数加一
        if isPerfact(i) and isSame(i):
            print(i)
            count = count + 1
    print("满足条件的数公有" + str(count) + "个")


main()
