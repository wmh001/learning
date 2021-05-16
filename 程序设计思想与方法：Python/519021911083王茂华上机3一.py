# -*-coding:utf-8-*-

# 动画:皮球从高处落地弹起
# 假设速度矢量向下为正，向上为负(注意坐标系方向)
# 且以皮球距地面高度(而非纵坐标)为位置变量
# 则主要计算公式为
# 球的新高度 = 球的旧高度 - 球速 * 时间间隔
# 球的新速度 = 球的旧速度 + 9.8 * 时间间隔
# 落地反弹:if 新高度 < 球半径：
# 应设置新高度=球半径
# 然后速度方向取反

from time import sleep
import tkinter


def main():
    # 创建根窗口
    root = tkinter.Tk()
    # 创建画布，宽300，高200，白色
    c = tkinter.Canvas(root, width=600, height=400, bg="white")
    # 布置画布
    c.pack()
    # 画地面
    c.create_rectangle(0, 375, 600, 375, fill='brown')
    # 画球
    ball = c.create_oval(300, 50, 350, 100, fill='brown', outline='white')
    # 设定初始高度
    h = 300
    # 设定初始速度
    v = 0
    # 设定时间间隔
    dt = 0.04
    while True:
        # 计算新高度
        new_h = h - v * dt
        # 计算新速度
        new_v = v + 9.8 * dt
        # 落地反弹
        if new_h < 25:
            new_h = 25
            new_v = -new_v
        # 计算高度差
        dh = new_h - h
        # 计算纵坐标差
        dy = -dh
        # 移动图形
        c.move(ball, 0, dy)
        # 画面更新
        c.update()
        # 高度更新
        h = new_h
        # 速度更新
        v = new_v

        sleep(0.02)


main()
