# -*-coding:utf-8-*-

import tkinter
from math import sin, cos, pi
from time import sleep
# 案例2：天体运动动画


def main():
    root = tkinter.Tk()
    c = tkinter.Canvas(root, width=300, height=200, bg='white')
    c.pack()

    c.create_oval(50, 50, 250, 150)
    c.create_oval(110, 85, 140, 115, fill='red')
    earth = c.create_oval(245, 95, 255, 105, fill='blue')
    moon = c.create_oval(265, 98, 270, 103)

    eX = 250
    eY = 100
    m2eX = 20
    m2eY = 0
    t = 0
    while True:
        t = t + 0.01 * pi
        new_eX = 150 + 100 * cos(t)
        new_eY = 100 - 50 * sin(t)
        new_m2eX = 20 * cos(12 * t)
        new_m2eY = -15 * sin(12 * t)

        edx = new_eX - eX
        edy = new_eY - eY
        mdx = new_m2eX - m2eX
        mdy = new_m2eY - m2eY

        c.move(earth, edx, edy)
        c.move(moon, mdx + edx, mdy + edy)
        c.update()

        eX = new_eX
        eY = new_eY
        m2eX = new_m2eX
        m2eY = new_m2eY

        sleep(0.04)


main()
