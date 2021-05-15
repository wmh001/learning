# -*-coding:utf-8-*-

import tkinter
# 案例1：统计图表


def getMarks():
    a, b, c, d, f = 0, 0, 0, 0, 0
    mark = int(input("Enter a mark: "))
    while mark >= 0:
        if mark >= 90:
            a = a + 1
        elif mark >= 80:
            b = b + 1
        elif mark >= 70:
            c = c + 1
        elif mark >= 60:
            d = d + 1
        else:
            f = f + 1
        mark = int(input("Enter a marks: "))
    return a, b, c, d, f


def main():
    a, b, c, d, f = getMarks()

    win = tkinter.Tk()
    cv = tkinter.Canvas(win, width=300, height=200, bg="white")
    cv.pack()

    n = a + b + c + d + f
    eA, sA = 360.0 * a / n, 0
    eB, sB = 360.0 * b / n, eA
    eC, sC = 360.0 * c / n, eA + eB
    eD, sD = 360.0 * d / n, eA + eB + eC
    eF, sF = 360.0 * f / n, eA + eB + eC + eD

    bb = (90, 40, 210, 160)
    pieA = cv.create_arc(bb, start=sA, extent=eA, fill="yellow")
    pieB = cv.create_arc(bb, start=sB, extent=eB, fill="green")
    pieC = cv.create_arc(bb, start=sC, extent=eC, fill="black")
    pieD = cv.create_arc(bb, start=sD, extent=eD, fill="gray")
    pieF = cv.create_arc(bb, start=sF, extent=eF, fill="red")

    cv.create_rectangle(240, 40, 260, 50, fill="yellow")
    cv.create_rectangle(240, 40 + 24, 260, 50 + 24, fill="green")
    cv.create_rectangle(240, 40 + 48, 260, 50 + 48, fill="black")
    cv.create_rectangle(240, 40 + 72, 260, 50 + 72, fill="gray")
    cv.create_rectangle(240, 40 + 96, 260, 50 + 96, fill="red")

    cv.create_text(270, 40, text="A", anchor='n')
    cv.create_text(270, 40 + 24, text="B", anchor='n')
    cv.create_text(270, 40 + 48, text="C", anchor='n')
    cv.create_text(270, 40 + 72, text="D", anchor='n')
    cv.create_text(270, 40 + 96, text="F", anchor='n')

    piepct = cv.create_text(40, 100, text="")

    def inPieA(event):
        pct = "%5.1f%%" % (100.0 * a / n)
        cv.itemconfig(piepct, text=pct)

    def inPieB(event):
        pct = "%5.1f%%" % (100.0 * b / n)
        cv.itemconfig(piepct, text=pct)

    def inPieC(event):
        pct = "%5.1f%%" % (100.0 * c / n)
        cv.itemconfig(piepct, text=pct)

    def inPieD(event):
        pct = "%5.1f%%" % (100.0 * d / n)
        cv.itemconfig(piepct, text=pct)

    def inPieF(event):
        pct = "%5.1f%%" % (100.0 * f / n)
        cv.itemconfig(piepct, text=pct)

    # 画布与鼠标箭头进入区域绑定
    cv.tag_bind(pieA, "<Enter>", inPieA)
    cv.tag_bind(pieB, "<Enter>", inPieB)
    cv.tag_bind(pieC, "<Enter>", inPieC)
    cv.tag_bind(pieD, "<Enter>", inPieD)
    cv.tag_bind(pieF, "<Enter>", inPieF)

    win.mainloop()


main()
