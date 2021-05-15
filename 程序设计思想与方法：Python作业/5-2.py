import tkinter
"""
图像 = PhotoImage(file=.gif图像文件名)创建图像对象
"""
"""
画布.create_image(参考点横坐标, 参考点纵坐标, image=图像, 选项=值, ...)
参考点位置：anchor=字符串，'e'右，'s'下，'w'左，'n'上，'center'中心，'se'右下，'ne'右上，...，默认'center'
state, tags等
返回所创建图像的标识号
"""
root = tkinter.Tk()
c = tkinter.Canvas(root, width=600, height=400, bg="white")
c.pack()
pic = tkinter.PhotoImage(file="程序设计思想与方法：Python作业\\v2-1fe2eff8f4f95c901abb3682d97eda3c_b.gif")
c.create_image(150, 100, image=pic)

tkinter.mainloop()
