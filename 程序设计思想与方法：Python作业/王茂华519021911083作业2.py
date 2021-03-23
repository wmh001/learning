# 4-15
# 计算通过两点的直线的斜率
def slope(p1, p2):
    try:
        # 根据坐标计算直线斜率
        return (p2[1] - p1[1]) / (p2[0] - p1[0])
    # 如果两点横坐标相等即直线没有斜率，提醒并返回None
    except ZeroDivisionError:
        print("通过两点的直线没有斜率。")
        return


# 计算通过两点的直线在y轴上的截距
def intercept(p1, p2):
    try:
        # 根据坐标计算直线在y轴上的截距
        return (p1[0] * p2[1] - p2[0] * p1[1]) / (p1[0] - p2[0])
    # 如果两点横坐标相等即直线与y轴不相交，提醒并返回None
    except ZeroDivisionError:
        print("通过两点的直线与y轴平行。")
        return


# 例程
# 判断输入的字符串是否可以转换为数字
def isNum(str):
    try:
        float(str)
        # float()不报错，则可以转换为数字
        return True
    # float()报错，则不可以转换为数字
    except ValueError:
        return False


# 输入p1的横坐标
p11 = input("请输入点1横坐标：")
# 如果输入的字符串不是数字，提醒并重新输入
while not isNum(p11):
    print("输入不是数字，请重新输入！")
    p11 = input("请输入点1横坐标：")

# 输入p1的纵坐标
p12 = input("请输入点1纵坐标：")
# 如果输入的字符串不是数字，提醒并重新输入
while not isNum(p12):
    print("输入不是数字，请重新输入！")
    p12 = input("请输入点1纵坐标：")

# 生成元组
p1 = (float(p11), float(p12))

# 输入p2的横坐标
p21 = input("请输入点2横坐标：")
# 如果输入的字符串不是数字，提醒并重新输入
while not isNum(p21):
    print("输入不是数字，请重新输入！")
    p21 = input("请输入点2横坐标：")

# 输入p2的纵坐标
p22 = input("请输入点2纵坐标：")
# 如果输入的字符串不是数字，提醒并重新输入
while not isNum(p22):
    print("输入不是数字，请重新输入！")
    p22 = input("请输入点2纵坐标：")

# 生成元组
p2 = (float(p21), float(p22))

# 如果返回值不是None，输出结果
if slope(p1, p2) != None:
    print("通过两点的直线斜率是%.2f" % (slope(p1, p2)))
if intercept(p1, p2) != None:
    print("通过两点的直线在y轴上的截距是%.2f" % (intercept(p1, p2)))
