# -*-coding:utf-8-*-

import tkinter


# 事件编程
def canvasFunc(event):
    if c.itemcget(t, "text") == "Hello!":
        c.itemconfig(t, text="Goodbye!")
    else:
        c.itemconfig(t, text="Hello!")


def textFunc(event):
    if c.itemcget(t, "fill") != "white":
        c.itemconfig(t, fill="white")
    else:
        c.itemconfig(t, fill="black")


root = tkinter.Tk()
c = tkinter.Canvas(root, width=600, height=400, bg="white")
c.pack()
t = c.create_text(150, 100, text="Hello!")
# 画布与左键绑定
c.bind("<Button-1>", canvasFunc)
# 画布上文本与右键绑定
c.tag_bind(t, "<Button-3>", textFunc)
root.mainloop()
