# -*-coding:utf-8-*-
# 输入本金a,年利率i,年数n
# 计算今后n年的增值情况
# 计算公式是a*((1+i)**n)
# 并用柱状图表示(例如可画成下面形状)
# 注意最大高度应随a,i,n而定.
import tkinter


# 主函数
def main():
    try:
        # 输入本金、年利率、年数
        a = float(input("请输入本金： "))
        i = float(input("请输入年利率： "))
        n = int(input("请输入年数： "))
        # 画柱状图
        draw_column(a, i, n)
    # 输入非法
    except ValueError:
        print("输入非法！")


# 画柱状图
def draw_column(a, i, n):
    # 创建根窗口
    root = tkinter.Tk()
    # 创建画布，宽600，高1000，白色
    c = tkinter.Canvas(root, width=1000, height=600, bg="white")
    # 布置画布
    c.pack()
    # 画顶部的线
    c.create_line(10, 20, 1000-10, 20)
    # 画底部的线
    c.create_line(10, 600-20, 1000-10, 600-20)
    # 计算空白宽度
    space = 1000 / (3 * n + 1)
    # 计算初始横坐标
    x = space
    # 计算柱宽
    width = 2 * x
    # 计算最高柱的高度
    max_height = a * ((1 + i)**n) / 540
    # 依次画柱形
    for j in range(0, n):
        # 计算柱高
        column_height = a * ((1 + i)**j) / max_height
        # 画柱形
        c.create_rectangle(x, 600 - 20 - column_height, x + width, 600 - 20, fill='green')
        # 标数据
        total = "%0.2f" % (column_height * max_height)
        c.create_text(x + width / 2, 600 - 20 - column_height, text=total, anchor='s')
        # 横坐标迭代
        x += space + width
    root.mainloop()


main()
