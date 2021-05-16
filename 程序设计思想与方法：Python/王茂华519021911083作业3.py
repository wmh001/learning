# -*-coding:utf-8-*-

# 5-5
# 创建汉字文本
# 导入thinter模块
from tkinter import *
# 创建根窗口
root1 = Tk()
# 创建画布，宽300，高200，白色
c = Canvas(root1, width=300, height=200, bg="white")
# 布置画布
c.pack()
# 创建汉字文本
c.create_text(10, 10, text="汉字文本", anchor=NW)
root1.mainloop()

# 5-11
# 画一幅冬季景色
# 有雪人和圣诞树之类

# 创建根窗口
root2 = Tk()
# 创建画布，宽600，高400，白色
c = Canvas(root2, width=600, height=400, bg="white")
# 布置画布
c.pack()


# 依据雪人头部左上角参考点画雪人
def Draw_snowman(x, y):
    # 画头部
    c.create_oval(x, y, x + 40, y + 40)
    # 画躯干
    c.create_oval(x - 10, y + 40, x + 50, y + 100)
    # 画右眼
    c.create_oval(x + 10, y + 15, x + 16, y + 21, fill='black')
    # 画左眼
    c.create_oval(x + 24, y + 15, x + 30, y + 21, fill='black')
    # 画鼻子
    c.create_oval(x + 18, y + 21, x + 22, y + 25)
    # 画嘴
    c.create_arc(x + 8,
                 y + 15,
                 x + 32,
                 y + 30,
                 start=230,
                 extent=80,
                 style='arc')
    # 画右臂
    c.create_line(x - 10, y + 70, x - 30, y + 50)
    c.create_line(x - 30, y + 50, x - 36, y + 42)
    c.create_line(x - 30, y + 50, x - 40, y + 50)
    # 画左臂
    c.create_line(x + 50, y + 70, x + 70, y + 50)
    c.create_line(x + 70, y + 50, x + 76, y + 42)
    c.create_line(x + 70, y + 50, x + 80, y + 50)
    # 画红帽子
    c.create_polygon(x + 10, y, x + 30, y, x + 20, y - 25, fill='red')
    c.create_oval(x + 18, y - 29, x + 22, y - 25)


# 依据圣诞树树冠顶点参考点画圣诞树
def Draw_christmas_tree(x, y):
    # 画树冠
    c.create_polygon(x, y, x - 30, y + 30, x + 30, y + 30, fill='green')
    c.create_polygon(x, y + 30, x - 60, y + 90, x + 60, y + 90, fill='green')
    # 画树干
    c.create_rectangle(x - 15, y + 90, x + 15, y + 120, fill='brown')
    # 画圣诞树装饰
    c.create_oval(x - 5, y - 10, x + 5, y, fill='gold')
    c.create_oval(x - 11, y + 18, x - 5, y + 24, fill='red')
    c.create_oval(x + 12, y + 20, x + 18, y + 26, fill='yellow')
    c.create_oval(x - 33, y + 63, x - 27, y + 69, fill='red')
    c.create_oval(x + 42, y + 77, x + 48, y + 83, fill='yellow')
    c.create_oval(x + 2, y + 51, x + 8, y + 57, fill='orange')
    c.create_oval(x - 18, y + 80, x - 24, y + 86, fill='pink')


# 画冬季景色
Draw_snowman(200, 200)
Draw_christmas_tree(100, 100)
Draw_christmas_tree(450, 50)
Draw_christmas_tree(380, 200)
root2.mainloop()
