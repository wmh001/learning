# -*-coding:utf-8-*-
# 利用自顶向下设计方法编程：
# 假设某人从2000年1月1日开始“三天打鱼两天晒网”
# 输入此后任意一个日期
# 问此人在这一天是在打鱼还是在晒网？


# 主函数
def main():
    # 获取日期
    date = getdate()
    # 计算日期差
    difference = getdifference(date)
    # 判断打鱼还是晒网
    judge(difference)


# 获取日期
def getdate():
    # 获取年
    year = int(input("请输入年（2000年及以后）："))
    # 获取月
    mouth = int(input("请输入月："))
    # 获取月
    day = int(input("请输入日："))
    # 将年月日放入日期列表中
    date = [year, mouth, day]
    return date


# 依据日期计算日期差
def getdifference(date):
    # 日期差等于整年加整月加日
    difference = getyear(date[0]) + getmonth(date[0], date[1]) + getday(date[2])
    return difference


# 计算来自整年的日期差
def getyear(year):
    # 计算2000年到输入年之间有几个闰年
    k = leapyears(year)
    # 年份差乘365加闰年数等于来自整年的日期差
    n = (year - 2000) * 365 + k
    return n


# 计算来自整月的日期差
def getmonth(year, month):
    # 引入每月天数
    month_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    # 如果是闰年，第二月改为29天
    if (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)):
        month_days[1] = 29
    n = 0
    # 将之前月的天数累加计算来自整月的日期差
    for i in range(0, month - 1):
        n = n + month_days[i]
    return n


# 计算来自日的日期差
def getday(day):
    n = day
    return n


# 计算2000年到输入年之间有几个闰年
def leapyears(year):
    count = 0
    for i in range(2000, year):
        if i % 4 == 0 and (i % 100 != 0 or i % 400 == 0):
            count = count + 1
    return count


# 判断打鱼还是晒网
def judge(difference):
    m = difference % 5
    # 余数为1、2、3，打鱼
    if m == 1 or m == 2 or m == 3:
        print("此人在这一天在打鱼")
    # 否则晒网
    else:
        print("此人在这一天在晒网")


# 运行主程序
main()
