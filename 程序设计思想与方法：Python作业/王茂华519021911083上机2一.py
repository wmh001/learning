# -*-coding:utf-8-*-
# 输入一个数字不全相同的三位数
# 然后进行“重排求差”操作：
# 用这三个数字组成的最大数减去用这三个数字组成的最小数
# 再对所得到的差重复“重排求差”操作
# 直至“差”不再变化为止
# 输出操作过程
# 例如：输入422，输出
# 422－224＝198
# 981－189＝792
# 972－279＝693
# 963－369＝594
# 954－459＝495
# 954－459＝495


# 输入一个数字不全相同的三位数
num = input("请输入一个数字不全相同的三位数：")
# 将字符串转换为整数
Num = int(num)
# 获取个位数字
digit2 = Num % 10
# 去掉个位数字
Num = int(Num / 10)
# 获取十位数字
digit1 = Num % 10
# 去掉十位数字
Num = int(Num / 10)
# 获取百位数字
digit0 = Num
if (digit0 == digit1) and (digit1 == digit2):
    print("输入非法！")
else:
    # 大小排序
    digits = [digit0, digit1, digit2]
    digits.sort()
    # 计算最大数
    max = digits[2] * 100 + digits[1] * 10 + digits[0]
    # 计算最小数
    min = digits[0] * 100 + digits[1] * 10 + digits[2]
    # 计算差
    dif = max - min
    # 打印算式
    print(str(max) + " - " + str(min) + " = " + str(dif))
    # 循环迭代
    while True:
        Num = dif
        # 获取个位数字
        digit2 = Num % 10
        # 去掉个位数字
        Num = int(Num / 10)
        # 获取十位数字
        digit1 = Num % 10
        # 去掉十位数字
        Num = int(Num / 10)
        # 获取百位数字
        digit0 = Num
        # 大小排序
        digits = [digit0, digit1, digit2]
        digits.sort()
        # 计算最大数
        max = digits[2] * 100 + digits[1] * 10 + digits[0]
        # 计算最小数
        min = digits[0] * 100 + digits[1] * 10 + digits[2]
        # 打印算式
        print(str(max) + " - " + str(min) + " = " + str(max - min))
        # 如果差值没有变化，结束循环
        if max - min == dif:
            break
        # 否则，迭代差值
        else:
            dif = max - min
