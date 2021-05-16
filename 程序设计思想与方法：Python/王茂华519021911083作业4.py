# -*-coding:utf-8-*-

# 利用筛法找出小于等于n的所有质数
# 基本思想是
# 首先创建从2到n的数值列表
# 然后将列表的第一个数显示输出（是质数）
# 并从列表中删除该数的所有倍数
# 重复以上过程直至列表为空
# 例如
# 如果n为10
# 则初始列表为[2,3,4,5,6,7,8,9,10]
# 输出2，并删除2、4、6、8、10
# 现在列表为[3,5,7,9]
# 输出3，删除3、9
# 现在列表为[5,7]
# 输出5，并删除5
# 输出7，并删除7
# 至此列表为空，程序结束


# 创建列表
def create_list(n):
    # 创建从2到n的数值列表
    lis = list(range(2, n + 1))
    # 返回列表
    return lis


# 输出一个质数
def output_prime(lis):
    # 将列表的第一个数显示输出（是质数），并删除
    prime = lis.pop(0)
    print(prime, end='')
    # 计算倍数
    multiple = prime * 2
    # 从列表中删除该数的所有倍数
    while (len(lis) != 0) and (multiple <= lis[-1]):
        # 如果倍数在数组中，删除该数
        if multiple in lis:
            lis.remove(multiple)
        # 计算新倍数
        multiple = multiple + prime
    # 如果列表不空，打印"、"
    if len(lis) != 0:
        print("、", end='')


# 打印小于等于n的质数
def output(lis):
    print("小于等于n的质数有", end='')
    # 打印数字
    while(len(lis) != 0):
        output_prime(lis)


# 主函数
def main():
    # 输入一个大于1的整数n
    n = int(input("请输入一个大于1的整数n:"))
    # 创建数组
    List = create_list(n)
    # 打印小于等于n的质数
    output(List)


main()
