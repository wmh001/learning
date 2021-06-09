# -*-coding:utf-8-*-

# Author: 王茂华
# id:519021911083
# name:程序设计思想与方法（Python）大作业————挠度方程求解程序
# Version: 0.0.1

# 导入模块
import tkinter
from PIL import ImageGrab


# 挠度方程求解
class DeflectionEquationSolution:
    def __init__(self):
        # 创建根窗口
        self.root = tkinter.Tk()
        self.root.title("弯矩方程求解")

        # 定义宽度常数
        self.entry_width = 52
        self.label_width = 40
        self.canvas_width = 314

        # 创建菜单系统
        self.meun = tkinter.Menu(self.root)
        self.root.config(menu=self.meun)
        self.file_meun = tkinter.Menu(self.meun)
        self.beam_type_meun = tkinter.Menu(self.meun)
        self.cantilever_beam_type_meun = tkinter.Menu(self.beam_type_meun)
        self.simple_beam_type_meun = tkinter.Menu(self.beam_type_meun)
        self.help_meun = tkinter.Menu(self.root)
        self.meun.add_cascade(label="文件", menu=self.file_meun)
        self.file_meun.add_command(label="保存当前窗口", command=self.saveasjpg)
        self.file_meun.add_command(label="保存为文本", command=self.saveastxt)
        self.file_meun.add_command(label="退出", command=self.root.quit)
        self.meun.add_cascade(label="梁种类", menu=self.beam_type_meun)
        self.beam_type_meun.add_cascade(label="悬臂梁",
                                        menu=self.cantilever_beam_type_meun)
        self.cantilever_beam_type_meun.add_command(
            label="受力矩", command=self.cantilever_beam_moment_interface)
        self.cantilever_beam_type_meun.add_command(
            label="受力", command=self.cantilever_beam_power_interface)
        self.cantilever_beam_type_meun.add_command(
            label="受均布载荷", command=self.cantilever_beam_UL_interface)
        self.beam_type_meun.add_cascade(label="简支梁",
                                        menu=self.simple_beam_type_meun)
        self.simple_beam_type_meun.add_command(
            label="受力矩", command=self.simple_beam_moment_interface)
        self.simple_beam_type_meun.add_command(
            label="受力", command=self.simple_beam_power_interface)
        self.simple_beam_type_meun.add_command(
            label="受均布载荷", command=self.simple_beam_UL_interface)
        self.meun.add_cascade(label="帮助", menu=self.help_meun)
        self.help_meun.add_command(label="教程", command=self.course)
        self.help_meun.add_command(label="报告错误")
        self.help_meun.add_command(label="检查更新")
        self.help_meun.add_command(label="关于", command=self.about)

        # 创建欢迎界面
        self.initial_text = tkinter.Label(self.root,
                                          width=69,
                                          text="欢迎使用！\n请在上面菜单栏中选择梁的种类或获取帮助。")
        self.initial_text.config(font=("宋体", 20))
        self.initial_text.pack()

        self.label_list = []
        self.entry_list = []

        # 创建梁的构件
        # 创建广义力输入栏
        self.F_label = tkinter.Label(self.root,
                                     width=self.label_width,
                                     anchor='e')
        self.F_val = tkinter.StringVar()
        self.F_entry = tkinter.Entry(self.root,
                                     textvariable=self.F_val,
                                     width=self.entry_width)

        # 创建弹性模量输入栏
        self.E_label = tkinter.Label(self.root, text="弹性模量(单位为GPa)=")
        self.E_val = tkinter.StringVar()
        self.E_entry = tkinter.Entry(self.root,
                                     textvariable=self.E_val,
                                     width=self.entry_width)

        # 创建惯性矩输入栏
        self.I_label = tkinter.Label(self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.I_val = tkinter.StringVar()
        self.I_entry = tkinter.Entry(self.root,
                                     textvariable=self.I_val,
                                     width=self.entry_width)

        # 创建梁长输入栏
        self.l_label = tkinter.Label(self.root, text="梁长(单位为m)=")
        self.l_val = tkinter.StringVar()
        self.l_entry = tkinter.Entry(self.root,
                                     textvariable=self.l_val,
                                     width=self.entry_width)

        # 创建力端距输入栏
        self.a_label = tkinter.Label(self.root, text="受力点到左端的距离(单位为m)=")
        self.a_val = tkinter.StringVar()
        self.a_entry = tkinter.Entry(self.root,
                                     textvariable=self.a_val,
                                     width=self.entry_width)

        # 创建确定按钮
        self.beam_button = tkinter.Button(self.root, text="确定")

        # 创建挠度方程输出栏
        self.w_label = tkinter.Label(self.root, text="挠度方程(单位为m)：")
        self.w_val = tkinter.StringVar()
        self.w_entry = tkinter.Entry(self.root,
                                     textvariable=self.w_val,
                                     width=self.entry_width)
        self.w_entry.config(state='readonly')

        self.w_val2 = tkinter.StringVar()
        self.w_entry2 = tkinter.Entry(self.root,
                                      textvariable=self.w_val2,
                                      width=self.entry_width)
        self.w_entry2.config(state='readonly')

        # 创建端截面转角输出栏
        self.angle_label = tkinter.Label(self.root)
        self.angle_val = tkinter.StringVar()
        self.angle_entry = tkinter.Entry(self.root,
                                         textvariable=self.angle_val,
                                         width=self.entry_width)
        self.angle_entry.config(state='readonly')

        # 创建右端截面转角输出栏
        self.angleB_label = tkinter.Label(self.root, text="右端截面转角(单位为弧度)：")
        self.angleB_val = tkinter.StringVar()
        self.angleB_entry = tkinter.Entry(self.root,
                                          textvariable=self.angleB_val,
                                          width=self.entry_width)
        self.angleB_entry.config(state='readonly')

        # 创建示意图
        self.beam_canvas = tkinter.Canvas(self.root,
                                          width=self.canvas_width,
                                          height=161,
                                          bg="white")

        self.root.mainloop()

    # 保存当前窗口
    def saveasjpg(self):
        self.root.update()
        x = 1.25 * self.root.winfo_rootx()
        y = 1.25 * self.root.winfo_rooty()
        x1 = x + 1.25 * self.root.winfo_width()
        y1 = y + 1.25 * self.root.winfo_height()
        ImageGrab.grab().crop((x, y, x1, y1)).save("result.jpg")

    # 保存为文本
    def saveastxt(self):
        f = open("result.txt", 'w')
        for i in range(len(self.label_list)):
            if self.label_list[i] != -1:
                f.write(self.label_list[i]["text"] + self.entry_list[i].get() +
                        "\n")
            else:
                f.write("                                " +
                        self.entry_list[i].get() + "\n")
        f.close()

    # 布局方式1，适用于悬臂梁受力矩、悬臂梁受力、悬臂梁受均布载荷
    def arrange_Interface1(self):
        self.F_label.grid(row=0, column=0, sticky='E')
        self.label_list.append(self.F_label)
        self.F_entry.grid(row=0, column=1, sticky='E')
        self.entry_list.append(self.F_entry)
        self.F_val.set("2000")
        self.E_label.grid(row=1, column=0, sticky='E')
        self.label_list.append(self.E_label)
        self.E_entry.grid(row=1, column=1, sticky='E')
        self.entry_list.append(self.E_entry)
        self.E_val.set("200")
        self.I_label.grid(row=2, column=0, sticky='E')
        self.label_list.append(self.I_label)
        self.I_entry.grid(row=2, column=1, sticky='E')
        self.entry_list.append(self.I_entry)
        self.I_val.set("100")
        self.l_label.grid(row=3, column=0, sticky='E')
        self.label_list.append(self.l_label)
        self.l_entry.grid(row=3, column=1, sticky='E')
        self.entry_list.append(self.l_entry)
        self.l_val.set("1.5")
        self.beam_button.grid(row=4, column=0, columnspan=2)
        self.w_label.grid(row=5, column=0, sticky='E')
        self.label_list.append(self.w_label)
        self.w_entry.grid(row=5, column=1, sticky='E')
        self.entry_list.append(self.w_entry)
        self.w_val.set("")
        self.angle_label.grid(row=6, column=0, sticky='E')
        self.label_list.append(self.angle_label)
        self.angle_entry.grid(row=6, column=1, sticky='E')
        self.entry_list.append(self.angle_entry)
        self.angle_val.set("")
        self.beam_canvas.grid(row=0, column=2, rowspan=7)
        self.beam_canvas.delete("all")
        self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')

    # 布局方式2，适用于简支梁受力矩、简支梁受力
    def arrange_Interface2(self):
        self.F_label.grid(row=0, column=0, sticky='E')
        self.label_list.append(self.F_label)
        self.F_entry.grid(row=0, column=1, sticky='E')
        self.entry_list.append(self.F_entry)
        self.F_val.set("2000")
        self.E_label.grid(row=1, column=0, sticky='E')
        self.label_list.append(self.E_label)
        self.E_entry.grid(row=1, column=1, sticky='E')
        self.entry_list.append(self.E_entry)
        self.E_val.set("200")
        self.I_label.grid(row=2, column=0, sticky='E')
        self.label_list.append(self.I_label)
        self.I_entry.grid(row=2, column=1, sticky='E')
        self.entry_list.append(self.I_entry)
        self.I_val.set("100")
        self.l_label.grid(row=3, column=0, sticky='E')
        self.label_list.append(self.l_label)
        self.l_entry.grid(row=3, column=1, sticky='E')
        self.entry_list.append(self.l_entry)
        self.l_val.set("1.5")
        self.a_label.grid(row=4, column=0, sticky='E')
        self.label_list.append(self.a_label)
        self.a_entry.grid(row=4, column=1, sticky='E')
        self.entry_list.append(self.a_entry)
        self.a_val.set("1")
        self.beam_button.grid(row=5, column=0, columnspan=2)
        self.w_label.grid(row=6, column=0, sticky='E')
        self.label_list.append(self.w_label)
        self.w_entry.grid(row=6, column=1, sticky='E')
        self.entry_list.append(self.w_entry)
        self.w_val.set("")
        self.label_list.append(-1)
        self.w_entry2.grid(row=7, column=1, sticky='E')
        self.entry_list.append(self.w_entry2)
        self.w_val2.set("")
        self.angle_label.grid(row=8, column=0, sticky='E')
        self.label_list.append(self.angle_label)
        self.angle_entry.grid(row=8, column=1, sticky='E')
        self.entry_list.append(self.angle_entry)
        self.angle_val.set("")
        self.angleB_label.grid(row=9, column=0, sticky='E')
        self.label_list.append(self.angleB_label)
        self.angleB_entry.grid(row=9, column=1, sticky='E')
        self.entry_list.append(self.angleB_entry)
        self.angleB_val.set("")
        self.beam_canvas.grid(row=0, column=2, rowspan=7)
        self.beam_canvas.delete("all")
        self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')

    # 布局方式3，适用于简支梁受均布载荷
    def arrange_Interface3(self):
        self.F_label.grid(row=0, column=0, sticky='E')
        self.label_list.append(self.F_label)
        self.F_entry.grid(row=0, column=1, sticky='E')
        self.entry_list.append(self.F_entry)
        self.F_val.set("2000")
        self.E_label.grid(row=1, column=0, sticky='E')
        self.label_list.append(self.E_label)
        self.E_entry.grid(row=1, column=1, sticky='E')
        self.entry_list.append(self.E_entry)
        self.E_val.set("200")
        self.I_label.grid(row=2, column=0, sticky='E')
        self.label_list.append(self.I_label)
        self.I_entry.grid(row=2, column=1, sticky='E')
        self.entry_list.append(self.I_entry)
        self.I_val.set("100")
        self.l_label.grid(row=3, column=0, sticky='E')
        self.label_list.append(self.l_label)
        self.l_entry.grid(row=3, column=1, sticky='E')
        self.entry_list.append(self.l_entry)
        self.l_val.set("1.5")
        self.beam_button.grid(row=4, column=0, columnspan=2)
        self.w_label.grid(row=5, column=0, sticky='E')
        self.label_list.append(self.w_label)
        self.w_entry.grid(row=5, column=1, sticky='E')
        self.entry_list.append(self.w_entry)
        self.w_val.set("")
        self.angle_label.grid(row=6, column=0, sticky='E')
        self.label_list.append(self.angle_label)
        self.angle_entry.grid(row=6, column=1, sticky='E')
        self.entry_list.append(self.angle_entry)
        self.angle_val.set("")
        self.angleB_label.grid(row=7, column=0, sticky='E')
        self.label_list.append(self.angleB_label)
        self.angleB_entry.grid(row=7, column=1, sticky='E')
        self.angleB_val.set("")
        self.beam_canvas.grid(row=0, column=2, rowspan=7)
        self.beam_canvas.delete("all")
        self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')

    # 绘制悬臂梁
    def draw_cantilever_beam(self, self_canvas, x, y):
        self_canvas.create_line(x, y - 20, x, y + 20, width=3)
        self_canvas.create_line(x, y, x + 200, y)

    # 绘制简支梁
    def draw_simple_beam(self, self_canvas, x, y):
        self_canvas.create_line(x, y, x + 200, y)
        self_canvas.create_line(x - 5, y + 10, x, y, x + 5, y + 10)
        self_canvas.create_polygon(x + 195,
                                   y + 10,
                                   x + 200,
                                   y,
                                   x + 205,
                                   y + 10,
                                   fill="white",
                                   outline="black")
        self_canvas.create_line(x - 10, y + 10, x + 10, y + 10, width=3)
        self_canvas.create_oval(x + 193, y + 10, x + 197, y + 14)
        self_canvas.create_oval(x + 203, y + 10, x + 207, y + 14)
        self_canvas.create_line(x + 190, y + 14, x + 210, y + 14, width=3)

    # 绘制力矩
    def draw_moment(self, self_canvas, x, y, value):
        self_canvas.create_line(x, y - 20, x, y + 20)
        self_canvas.create_line(x, y - 20, x + 20, y - 20, arrow="last")
        self_canvas.create_line(x, y + 20, x - 20, y + 20, arrow="last")
        self_canvas.create_text(x + 10,
                                y - 20,
                                text="M=" + value + "N*m",
                                anchor='s')

    # 绘制力
    def draw_power(self, self_canvas, x, y, value):
        self_canvas.create_line(x, y - 40, x, y, arrow="last")
        self_canvas.create_text(x, y - 40, text="F=" + value + "N", anchor='s')

    # 绘制均布载荷
    def draw_UL(self, self_canvas, x, y, value):
        self_canvas.create_line(x, y - 20, x + 200, y - 20)
        self_canvas.create_line(x, y - 20, x, y, arrow="last")
        for i in range(20):
            self_canvas.create_line(x + 10 * (i + 1),
                                    y - 20,
                                    x + 10 * (i + 1),
                                    y,
                                    arrow="last")
        self_canvas.create_text(x + 100,
                                y - 20,
                                text="q=" + value + "N*m^(-1)",
                                anchor='s')

    # 错误警告
    def warning(self):
        self.warning_top = tkinter.Toplevel()
        self.warning_top.geometry("200x80")
        self.warning_top.title("警告")
        self.warning_label_1 = tkinter.Label(self.warning_top, text="!")
        self.warning_label_1.config(font=("宋体", 40), fg="red")
        self.warning_label_1.pack()
        self.warning_label_2 = tkinter.Label(self.warning_top,
                                             text="输入值无法计算，请检查输入！")
        self.warning_label_2.pack()

    # 布局力矩悬臂梁界面
    def cantilever_beam_moment_interface(self):
        # 删除多余构件
        self.initial_text.pack_forget()
        self.a_label.grid_forget()
        self.a_entry.grid_forget()
        self.w_entry2.grid_forget()
        self.angleB_label.grid_forget()
        self.angleB_entry.grid_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "力矩(单位为N*m，顺时针为正方向)="
        self.angle_label["text"] = "端截面转角(单位为弧度)："
        self.beam_button["command"] = self.cantilever_beam_moment_determine
        self.arrange_Interface1()

    # 显示力矩悬臂梁计算结果
    def cantilever_beam_moment_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            if (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = -float(self.F_entry.get()) / (2 * E * 10**9 * I_ /
                                                          10**8)
            angle_B = 2 * coefficient_w * L
            # 显示结果
            self.w_val.set("w=%0.7f*x^2" % coefficient_w)
            self.angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.beam_canvas, 50, 80)
            self.draw_moment(self.beam_canvas, 250, 80, self.F_entry.get())
            for i in range(0, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x**2
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 布局力悬臂梁界面
    def cantilever_beam_power_interface(self):
        # 删除多余构件
        self.initial_text.pack_forget()
        self.a_label.grid_forget()
        self.a_entry.grid_forget()
        self.w_entry2.grid_forget()
        self.angleB_label.grid_forget()
        self.angleB_entry.grid_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "力(单位为N，向下为正方向)="
        self.angle_label["text"] = "端截面转角(单位为弧度)："
        self.beam_button["command"] = self.cantilever_beam_power_determine
        self.arrange_Interface1()

    # 显示力悬臂梁计算结果
    def cantilever_beam_power_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            if (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = -float(self.F_entry.get()) / (6 * E * 10**9 * I_ /
                                                          10**8)
            intercept = 3 * L
            angle_B = 3 * coefficient_w * L**2
            # 显示结果
            self.w_val.set("w=%0.7f*x^2*(%0.2f-x)" %
                           (coefficient_w, intercept))
            self.angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.beam_canvas, 50, 80)
            self.draw_power(self.beam_canvas, 250, 80, self.F_entry.get())
            for i in range(0, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x**2 * (3 * L - x)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 布局均布载荷悬臂梁界面
    def cantilever_beam_UL_interface(self):
        # 删除多余构件
        self.initial_text.pack_forget()
        self.a_label.grid_forget()
        self.a_entry.grid_forget()
        self.w_entry2.grid_forget()
        self.angleB_label.grid_forget()
        self.angleB_entry.grid_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "均布载荷集度(单位为N*m^(-1))，向下为正方向)="
        self.angle_label["text"] = "端截面转角(单位为弧度)："
        self.beam_button["command"] = self.cantilever_beam_UL_determine
        self.arrange_Interface1()

    # 显示均布载荷悬臂梁计算结果
    def cantilever_beam_UL_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            if (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = -float(self.F_entry.get()) / (24 * E * 10**9 * I_ /
                                                          10**8)
            coefficient_x = -4 * L
            intercept = 6 * L**2
            angle_B = 4 * coefficient_w * L**3
            # 显示结果
            self.w_val.set("w=%0.7f*x^2*(x^2%0.2f*x+%0.2f)" %
                           (coefficient_w, coefficient_x, intercept))
            self.angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.beam_canvas, 50, 80)
            self.draw_UL(self.beam_canvas, 50, 80, self.F_entry.get())
            for i in range(0, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x**2 * (x**2 - 4 * L * x + 6 * L**2)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 布局力矩简支梁界面
    def simple_beam_moment_interface(self):
        # 删除多余构件
        self.initial_text.pack_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "力矩(单位为N*m，顺时针为正方向)="
        self.angle_label["text"] = "左端截面转角(单位为弧度)："
        self.beam_button["command"] = self.simple_beam_moment_determine
        self.arrange_Interface2()

    # 显示力矩简支梁计算结果
    def simple_beam_moment_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            a = float(self.a_entry.get())
            b = L - a
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            # 力端距大于梁长报错
            if (b < 0) or (a < 0) or (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = float(
                self.F_entry.get()) / (6 * E * 10**9 * I_ / 10**8 * L)
            angle_A = coefficient_w * (L**2 - 3 * b**2)
            angle_B = coefficient_w * (L**2 - 3 * a**2)
            # 显示结果
            self.angle_val.set("%0.7f " % angle_A)
            self.angleB_val.set("%0.7f " % angle_B)
            if a == 0:
                self.w_val.set("w=-%0.7f*x*(%0.2f-x)(%0.2f-x" %
                               (coefficient_w, L, 2 * L))
                self.w_val2.set("-------------------------")
            elif b == 0:
                self.w_val.set("w=%0.7f*x*(%0.2f-x^2)" % (coefficient_w, L**2))
                self.w_val2.set("-------------------------")
            else:
                self.w_val.set("w=%0.7f*x*(%0.2f-x^2)(0≤x≤%0.2f)" %
                               (coefficient_w, L**2 - 3 * b**2, a))
                self.w_val2.set(
                    "w=%0.7f*(-x^3+%0.2f*(x-%0.2f)^2+%0.2f*x)(%0.2f≤x≤%0.2f)" %
                    (coefficient_w, 3 * L, a, L**2 - 3 * b**2, a, L))
            # 绘制示意图
            self.draw_simple_beam(self.beam_canvas, 50, 80)
            self.draw_moment(self.beam_canvas, 50 + 200 * a / L, 80,
                             self.F_entry.get())
            last = int(20 * a / L)
            for i in range(0, last):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x * (L**2 - 3 * b**2 - x**2)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
            for i in range(last, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * (-x**3 + 3 * L * (x - a)**2 +
                                         (L**2 - 3 * b**2) * x)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 布局力简支梁界面
    def simple_beam_power_interface(self):
        # 删除多余构件
        self.initial_text.pack_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "力(单位为N，向下为正方向)="
        self.angle_label["text"] = "左端截面转角(单位为弧度)："
        self.beam_button["command"] = self.simple_beam_power_determine
        self.arrange_Interface2()

    # 显示力简支梁计算结果
    def simple_beam_power_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            a = float(self.a_entry.get())
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            b = L - a
            # 力端距大于梁长报错
            if (b < 0) or (a < 0) or (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = -float(self.F_entry.get()) * b / (6 * E * 10**9 *
                                                              I_ / 10**8 * L)
            angle_A = coefficient_w * a * (L + b)
            angle_B = -coefficient_w * a * (L + a)
            # 显示结果
            self.angle_val.set("%0.7f " % angle_A)
            self.angleB_val.set("%0.7f " % angle_B)
            if (a == 0) or (b == 0):
                self.w_val.set("w=0")
                self.w_val2.set("-------------------------")
            else:
                self.w_val.set("w=%0.7f*x*(%0.2f-x^2)(0≤x≤%0.2f)" %
                               (coefficient_w, L**2 - b**2, a))
                self.w_val2.set(
                    "w=%0.7f*(%0.2f*(x-%0.2f)^3+%0.2f*x-x^3)(%0.2f≤x≤%0.2f)" %
                    (coefficient_w, L / b, a, L**2 - b**2, a, L))
            # 绘制示意图
            self.draw_simple_beam(self.beam_canvas, 50, 80)
            self.draw_power(self.beam_canvas, 50 + 200 * a / L, 80,
                            self.F_entry.get())
            last = int(20 * a / L)
            for i in range(0, last):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x * (L**2 - b**2 - x**2)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
            for i in range(last, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * (L / b * (x - a)**3 +
                                         (L**2 - b**2) * x - x**3)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 布局均布载荷简支梁界面
    def simple_beam_UL_interface(self):
        # 删除多余组件
        self.initial_text.pack_forget()
        self.a_label.grid_forget()
        self.a_entry.grid_forget()
        self.w_entry2.grid_forget()
        self.label_list = []
        self.entry_list = []
        # 更改构件
        self.F_label["text"] = "均布载荷集度(单位为N*m^(-1))，向下为正方向)="
        self.angle_label["text"] = "左端截面转角(单位为弧度)："
        self.beam_button["command"] = self.simple_beam_UL_determine
        self.arrange_Interface3()

    # 显示均布载荷计算结果
    def simple_beam_UL_determine(self):
        try:
            # 更新示意图
            self.beam_canvas.delete("all")
            self.beam_canvas.create_text(150, 160, text="示意图", anchor='s')
            # 计算参数
            L = float(self.l_entry.get())
            E = float(self.E_entry.get())
            I_ = float(self.I_entry.get())
            if (L <= 0) or (E < 0) or (I_ < 0):
                self.warning()
                return
            coefficient_w = -float(self.F_entry.get()) / (24 * E * 10**9 * I_ /
                                                          10**8)
            angle_A = coefficient_w * L**3
            angle_B = -angle_A
            # 显示结果
            self.angle_val.set("%0.7f " % angle_A)
            self.angleB_val.set("%0.7f " % angle_B)
            self.w_val.set("w=%0.7f*x*(%0.2f-%0.2f*x^2+x^3)" %
                           (coefficient_w, L**3, 2 * L))
            # 绘制示意图
            self.draw_simple_beam(self.beam_canvas, 50, 80)
            self.draw_UL(self.beam_canvas, 50, 80, self.F_entry.get())
            for i in range(0, 20):
                point = ()
                for j in range(0, 6):
                    x = (10 * i + j) / 200 * L
                    w = coefficient_w * x * (x**3 - 2 * L * x**2 + L**3)
                    point = point + (50 + 10 * i + j, 80 - 5000 * w)
                self.beam_canvas.create_line(point, smooth=1, fill="red")
        except:
            self.warning()

    # 显示教程窗口
    def course(self):
        self.help_top = tkinter.Toplevel()
        self.help_top.title("教程")
        self.help_label = tkinter.Label(
            self.help_top,
            justify="left",
            text="使用步骤如下：\n1.从菜单栏中选择梁的种类和受力类型；\n2.输入受\
力值、弹性模量、惯性矩等参数；\n3.点击确定按钮，从下面文本框可以读取挠度方程和端截\
面转角，从右侧可以看到受力示意图和弯曲后的轴线（红色虚线）。\n\n其他功能：点击菜单\
栏中“文件”后，点击“保存当前窗口”可以保存当前窗口为.jpg文件；点击“保存为文本”可以保\
持当前输入的\n参数和显示结果为.txt文件；点击“退出”可以退出程序；\n\n注：\n1.此处计\
算结果仅适用于弹性范围内；\n2.此处仅可以计算悬臂梁和简支梁模型，外伸梁可以基于这两\
种情况用叠加法计算；\n3.由于此处解算进行了平截面假设、对称弯曲假设和纯弯曲假设，计\
算结果仅适用于横截面关于剪力方向对称的细长梁；\n4.此处仅计算受力点在自由端或全梁受\
均布载荷等最基本情况，其他情况可以根据端截面转角或叠加法方便地算出；\n5.在工程中，\
挠度相对跨度极小，因此图中弯曲后的直线是挠度增大到原来的5000倍的结果。\n6.“保存当\
前窗口”功能仅适用于显示缩放大小为125%的电脑；\n7.“保存为文本”功能仅保存当前界面参\
数和计算结果，不能检测当前参数是否可以计算和当前结果是否为当前参数计算出；")
        self.help_label.pack()

    # 显示关于窗口
    def about(self):
        self.about_top = tkinter.Toplevel()
        self.about_top.geometry("200x100")
        self.about_top.title("关于")
        self.about_label = tkinter.Label(self.about_top,
                                         justify="left",
                                         text="弯矩方程求解\n\n版本号：0.0.1\
\n权利声明：xxxxxx\n网址：xxxxxx")
        self.about_label.pack()


if __name__ == '__main__':
    d = DeflectionEquationSolution()
