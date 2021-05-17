# -*-coding:utf-8-*-
# 图形编程

import tkinter
"""
Tk()创建窗口
返回窗口对象
"""
root = tkinter.Tk()
"""
Canvas(窗口, 选项1 = 值1, ...)创建画布
窗口宽度：width=整型数（单位：像素），默认使已画图形居中
窗口高度：height=整型数（单位：像素），默认使已画图形居中
画布颜色：bg=字符串，默认'white'
返回画布类型
"""
c = tkinter.Canvas(root, width=600, height=400, bg="white")
"""
画布.pack()布置画布
画布上建立坐标系，x轴向右，y轴向下，单位为像素
"""
c.pack()

"""
画布.create_rectangle(左上角横坐标, 左上角纵坐标, 右下角横坐标, 右下角纵坐标, 选项=值, ...)
画布.create_rectangle(左上角坐标, 右下角坐标, 选项=值, ...)
画布.create_rectangle(坐标元组, 选项=值, ...)绘制矩形
边框颜色：outline=字符串，默认'black'
填充颜色：fill=字符串，默认''
可见/隐藏：State=NORMAL/HIDDEN或state='normal'/'hidden'，默认NORMAL
虚线线长,虚线间隔：dash=元组，默认(∞, 0)实线
标签：tags=字符串(标签可以代替图形标识号)
返回图形标识号
"""
r1 = c.create_rectangle(150, 150, 300, 200, dash=(1, 1), tags="rect#2")
"""
p1 = (50, 50)
p2 = (200, 100)
r1 = c.create_rectangle(p1, p2, dash=(1, 1))
"""
"""
xy = (50, 50, 200, 100)
r1 = c.create_rectangle(xy, dash=(1, 1))
"""
r2 = c.create_rectangle(80, 70, 240, 150)
"""
画布.delete(图形标识号)删除画布上的图形
"""
c.delete(r2)
"""
画布.move(图形标识号, x轴向移动距离, y轴向移动距离)移动画布上的图形
"""
c.move(1, 50, 50)
"""
画布.itemconfig(图形标识号, 选项=值, ...)设置选项
"""
c.itemconfig(r1, fill="red")
c.itemconfig('rect#2', outline='green')
"""
画布.itemcget(图形标识号, '选项名', ...)获取选项的值
"""
"""
画布.create_oval(左上角横坐标, 左上角纵坐标, 右下角横坐标, 右下角纵坐标, 选项=值, ...)画左上角和右下角矩形中的内接椭圆
边框颜色：outline=字符串，默认'black'
填充颜色：fill=字符串，默认''
可见/隐藏：state=字符串，'normal'可见，'hidden'隐藏，默认'normal'
虚线线长,虚线间隔：dash=元组，默认(∞, 0)实线，(x,)表示(x, x)
返回图形标识号
"""
o1 = c.create_oval(50, 50, 250, 150)
o2 = c.create_oval(110, 85, 140, 115, fill='red')
o3 = c.create_oval(245, 95, 255, 105, fill='blue')
"""
画布.create_arc(左上角横坐标, 左上角纵坐标, 右下角横坐标, 右下角纵坐标, 选项=值, ...)画左上角和右下角矩形中的内接椭圆的一部分——弧形
开始位置：start=整型数（水平向右为极轴，单位：角度），默认0
逆时针旋转的角度：extent=整型数（单位：角度），默认90
模式：style=字符串，'pieslice'扇形，'arc'弧形，'chord'弓形，默认'pieslice'
线宽：width=整型数（单位：像素）
outline,fill,state, dash等
返回图形标识号
"""
bbox = (250, 250, 450, 350)
c.create_arc(bbox)
c.create_arc(bbox, start=100, extent=140, style="arc", width=4)
c.create_arc(bbox, start=250, extent=110, style="chord")
"""
画布.create_line(点1横坐标, 点1纵坐标, 点2横坐标, 点2纵坐标, ..., 选项=值, ...)画线段及折线
光滑度：smooth=整型数，0折线，非0平滑曲线，默认0
箭头：arrow=字符串，'none'没有，'first'起点有，'last'终点有，'both'双向，默认'none'
arrowshape=(d1,d2,d3)
fill,state, dash等
返回图形标识号
"""
s1 = (320, 20)
s2 = (360, 40)
s3 = (380, 60)
s4 = (385, 80)
s5 = (370, 100)
s6 = (385, 115)
s7 = (410, 100)
polaris = (520, 40)
# 画点
c.create_oval(s1, (323, 23), fill='black')
c.create_oval(s2, (363, 43), fill='black')
c.create_oval(s3, (383, 63), fill='black')
c.create_oval(s4, (388, 83), fill='black')
c.create_oval(s5, (373, 103), fill='black')
c.create_oval(s6, (388, 118), fill='black')
c.create_oval(s7, (413, 103), fill='black')
c.create_oval((522, 36), (526, 42), fill='black')
# 连线
c.create_line(s1, s2, s3, s4, s5, s6, s7, s4)
c.create_line(s7, polaris, dash=(4,), arrow='last')
c.create_line(305, 190, 450, 160, 595, 190, smooth=1)
"""
画布.create_polygon(点1横坐标, 点1纵坐标, 点2横坐标, 点2纵坐标, ..., 选项=值, ...)画多边形
光滑度：smooth=整型数，0折线，非0平滑曲线，默认0
边框颜色：outline=字符串，默认''
填充颜色：fill=字符串，默认'black'
state, dash等
返回图形标识号
"""
p11, p21, p31 = (70, 220), (70 + 100, 220), (70, 220 + 100)
p12, p22, p32 = (35, 250), (35 + 100, 250), (35, 250 + 100)
p13, p23, p33 = (55, 285), (55 + 100, 285), (55, 285 + 100)
p14, p24, p34 = (85, 285), (85 + 100, 285), (85, 285 + 100)
p15, p25, p35 = (105, 250), (105 + 100, 250), (105, 250 + 100)
c.create_polygon(p11, p12, p13, p14, p15)
c.create_polygon(p21, p23, p25, p22, p24, outline="black", fill="")
c.create_polygon(p31, p32, p33, p34, p35, outline="black", fill="")
"""
画布.create_text(参考点横坐标, 参考点纵坐标, 选项=值, ...)创建文字
文本内容：text=字符串
参考点位置：anchor=字符串，'e'右，'s'下，'w'左，'n'上，'center'中心，'se'右下，'ne'右上，...，默认'center'
对齐方式：justify=字符串，'left'左对齐，'center'中心对齐，'right'右对齐，默认'left'
fill,state, dash等
返回图形标识号
"""
root2 = tkinter.Tk()
c2 = tkinter.Canvas(root2, width=300, height=200, bg="white")
c2.pack()
c2.create_text(10, 10, text="NW@(10,10)", anchor='nw')
c2.create_text(150, 10, text="N@(150,10)", anchor='n')
c2.create_text(290, 10, text="NE@(290,10)", anchor='ne')
c2.create_text(10, 100, text="W@(10,100)", anchor='w')
c2.create_text(150, 100, text="CENTER@(150,100)\n2nd Line")
c2.create_text(290, 100, text="E@(290,100)", anchor='e')
c2.create_text(10, 200, text="SW@(10,200)", anchor='sw')
c2.create_text(150, 200, text="S@(150,200)", anchor='s')
c2.create_text(290, 200, text="SE@(290,200)", anchor='se')

tkinter.mainloop()
