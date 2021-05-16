# -*-coding:utf-8-*-

# 从Canvas下载人口普查数据文件data.txt
# 文件每一行是用逗号分隔的15个数据
# 如第1行是：
# 25, Private, 226802, 11th, 7, Never-married, Machine-op-inspct, Own-child, Black, Male, 0, 0, 40, United-States, <=50K
# 15个数据中，第4，9，10，15个数据的含义如下（x表示忽略其他11个数据）：
# x，x，x，教育程度，x，x，x，x，种族，性别，x，x，x，x，收入
# 这四个数据可能取的值分别是：
# 教育程度值: Preschool, 1st-4th, 5th-6th, 7th-8th, 9th, 10th, 11th,12th,
#            HS-grad, Assoc-acdm, Assoc-voc, Prof-school, Some-college, Bachelors, Masters, Doctorate
# 种族值: White, Black, Asian-Pac-Islander, Amer-Indian-Eskimo, Other.
# 性别值: Female, Male.
# 收入值：<=50K, >50K
# 按如下分类，分别统计各类人群的收入情况，即某类人群中<=50K和>50K的各占多少？
# 教育：有学位的人（Bachelors/Masters/Doctorate） vs 其他人
# 种族：白人（White）vs 其他人
# 性别：男人（Male）vs 女人（Female）
# 用图形给出直观的结果（例如用分为两色的柱状图表示各占的比例）。

import tkinter


# 主函数
def main():
    # 读取文件并统计数据
    dh, dl, ndh, ndl, wh, wl, ch, cl, mh, ml, fh, fl = read_and_count()
    # 画图
    draw(dh, dl, ndh, ndl, wh, wl, ch, cl, mh, ml, fh, fl)


# 字符串预处理
def pretreat(s):
    s = s.replace(',', ' ')
    s = s.replace('.', ' ')
    return s


# 读取和统计
def read_and_count():
    # 打开文件
    f = open("data.txt", 'r')
    s = f.readline()
    # 变量初始化
    dh = 0
    dl = 0
    ndh = 0
    ndl = 0
    wh = 0
    wl = 0
    ch = 0
    cl = 0
    mh = 0
    ml = 0
    fh = 0
    fl = 0
    while s != "":
        # 字符串预处理
        s = pretreat(s)
        # 单词划分
        wordlist = s.split()
        if wordlist[3] == "Bachelors" or wordlist[3] == "Masters" or wordlist == "Doctorate":
            # 有学位高收入
            if '>' in wordlist[14]:
                dh = dh + 1
            # 有学位低收入
            else:
                dl = dl + 1
        else:
            # 无学位高收入
            if '>' in wordlist[14]:
                ndh = ndh + 1
            # 无学位低收入
            else:
                ndl = ndl + 1

        if wordlist[8] == "White":
            # 白人高收入
            if '>' in wordlist[14]:
                wh = wh + 1
            # 白人低收入
            else:
                wl = wl + 1
        else:
            # 有色人高收入
            if '>' in wordlist[14]:
                ch = ch + 1
            # 有色人低收入
            else:
                cl = cl + 1

        if wordlist[9] == "Male":
            # 男性高收入
            if '>' in wordlist[14]:
                mh = mh + 1
            # 男性低收入
            else:
                ml = ml + 1
        else:
            # 女性高收入
            if '>' in wordlist[14]:
                fh = fh + 1
            # 女性低收入
            else:
                fl = fl + 1
        # 读取下一行
        s = f.readline()

    return dh, dl, ndh, ndl, wh, wl, ch, cl, mh, ml, fh, fl


# 画一组柱形
def draw_column(c, h1, l1, h2, l2, k, t):
    # 类一总数
    first = h1 + l1
    # 类二总数
    second = h2 + l2
    # 计算总数
    total = first + second
    # 计算坐标并画矩形
    x0 = 40 + (k-1)*220
    y0 = 340 - h1 * 340 / total
    x1 = x0 + 45
    y1 = 340
    c.create_rectangle(x0, y0, x1, y1, fill='green')
    y2 = y0 - l1 * 340 / total
    c.create_rectangle(x0, y2, x1, y0, fill='red')
    u0 = x1
    v0 = 340 - h2 * 340/total
    u1 = u0 + 45
    v1 = 340
    c.create_rectangle(u0, v0, u1, v1, fill='green')
    v2 = v0 - l2 * 340 / total
    c.create_rectangle(u0, v2, u1, v0, fill='red')

    # 标注类别
    c.create_text(x0 + 4, 344, text=t[0], anchor='nw')
    c.create_text(u0 + 4, 344, text=t[1], anchor='nw')

    # 标注比例
    pro1 = "%0.2f%%" % (100*h1/first)
    c.create_text(x0, y1, text=pro1, anchor='sw')
    pro2 = "%0.2f%%" % (100*h2/second)
    c.create_text(u0, v1, text=pro2, anchor='sw')

    pro3 = "%0.2f%%" % (100*l1/first)
    c.create_text(x0, y2, text=pro3, anchor='nw')
    pro4 = "%0.2f%%" % (100*l2/second)
    c.create_text(u0, v2, text=pro4, anchor='nw')


def draw(dh, dl, ndh, ndl, wh, wl, ch, cl, mh, ml, fh, fl):
    # 创建根窗口
    root = tkinter.Tk()
    # 创建画布，宽300，高200，白色
    c = tkinter.Canvas(root, width=600, height=400, bg="white")
    # 布置画布
    c.pack()
    # 分别画三组柱形
    draw_column(c, dh, dl, ndh, ndl, 1, ["有\n学\n位", "无\n学\n位"])
    draw_column(c, wh, wl, ch, cl, 2, ["白\n人", "有\n色\n人"])
    draw_column(c, mh, ml, fh, fl, 3, ["男\n性", "女\n性"])

    root.mainloop()


main()
