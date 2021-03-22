# 4-15
# 计算通过两点的直线的斜率
def slope(p1, p2):
    try:
        return (p2[1] - p1[1]) / (p2[0] - p1[0])
    except ZeroDivisionError:
        print("通过两点的直线没有斜率。")
        return


# 计算通过两点的直线在y轴上的截距
def intercept(p1, p2):
    try:
        return (p1[0] * p2[1] - p2[0] * p1[1]) / (p1[0] - p2[0])
    except ZeroDivisionError:
        print("通过两点的直线与y轴平行。")
        return


# 例程
def isNum(str):
    try:
        float(str)
        return True
    except ValueError:
        return False


p11 = input("请输入点1横坐标：")
while not isNum(p11):
    print("输入不是数字，请重新输入！")
    p11 = input("请输入点1横坐标：")

p12 = input("请输入点1纵坐标：")
while not isNum(p12):
    print("输入不是数字，请重新输入！")
    p12 = input("请输入点1纵坐标：")

p1 = (float(p11), float(p12))

p21 = input("请输入点2横坐标：")
while not isNum(p21):
    print("输入不是数字，请重新输入！")
    p21 = input("请输入点2横坐标：")

p22 = input("请输入点2纵坐标：")
while not isNum(p22):
    print("输入不是数字，请重新输入！")
    p22 = input("请输入点2纵坐标：")

p2 = (float(p21), float(p22))

if slope(p1, p2) != None:
    print("通过两点的直线斜率是" + str(slope(p1, p2)))
if intercept(p1, p2) != None:
    print("通过两点的直线在y轴上的截距是" + str(intercept(p1, p2)))
