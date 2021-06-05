# -*-coding:utf-8-*-

import tkinter

# entry_width = 35


class deflectionEquationCalculator:
    def __init__(self):
        self.root = tkinter.Tk()
        self.root.title("弯矩方程计算器")
        self.root.geometry("600x400")
        self.entry_width = 35

        self.meun = tkinter.Menu(self.root)
        self.root.config(menu=self.meun)
        self.beam_type_meun = tkinter.Menu(self.meun)
        self.cantilever_beam_type_meun = tkinter.Menu(self.beam_type_meun)
        self.help_meun = tkinter.Menu(self.root)
        self.meun.add_cascade(label="梁的种类", menu=self.beam_type_meun)
        self.beam_type_meun.add_cascade(label="悬臂梁",
                                        menu=self.cantilever_beam_type_meun)
        self.cantilever_beam_type_meun.add_command(
            label="受端力矩", command=self.cantilever_beam_moment_interface)
        self.cantilever_beam_type_meun.add_command(
            label="受端力", command=self.cantilever_beam_power_interface)
        self.meun.add_cascade(label="帮助", menu=self.help_meun)
        self.help_meun.add_command(label="教程", command=self.course)
        self.help_meun.add_command(label="关于", command=self.about)

        self.initial_text = tkinter.Label(self.root,
                                          text="欢迎使用！\n请在上面菜单栏中选择梁的种类或获取帮助。")
        self.initial_text.config(font=("宋体", 20))
        self.initial_text.pack()

        self.cantilever_beam_moment_list = []

        self.cantilever_beam_moment_M_label = tkinter.Label(
            self.root, text="力矩(单位为N*m，顺时针为正方向)=")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_M_label)
        self.cantilever_beam_moment_M_val = tkinter.StringVar()
        self.cantilever_beam_moment_M_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_M_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_M_entry)

        self.cantilever_beam_moment_E_label = tkinter.Label(
            self.root, text="弹性模量(单位为GPa)=")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_E_label)
        self.cantilever_beam_moment_E_val = tkinter.StringVar()
        self.cantilever_beam_moment_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_E_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_E_entry)

        self.cantilever_beam_moment_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^(-4))=")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_I_label)
        self.cantilever_beam_moment_I_val = tkinter.StringVar()
        self.cantilever_beam_moment_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_I_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_I_entry)

        self.cantilever_beam_moment_l_label = tkinter.Label(self.root,
                                                            text="梁长(单位为m)=")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_l_label)
        self.cantilever_beam_moment_l_val = tkinter.StringVar()
        self.cantilever_beam_moment_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_l_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_l_entry)

        self.cantilever_beam_moment_button = tkinter.Button(
            self.root,
            text="确定",
            command=self.cantilever_beam_moment_determine)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_button)

        self.cantilever_beam_moment_w_label = tkinter.Label(self.root,
                                                            text="挠度方程(单位为m)：")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_w_label)
        self.cantilever_beam_moment_w_val = tkinter.StringVar()
        self.cantilever_beam_moment_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_w_val,
            width=self.entry_width)
        self.cantilever_beam_moment_w_entry.config(state='readonly')
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_w_entry)

        self.cantilever_beam_moment_angle_label = tkinter.Label(
            self.root, text="端截面转角(单位为弧度)：")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_angle_label)
        self.cantilever_beam_moment_angle_val = tkinter.StringVar()
        self.cantilever_beam_moment_angle_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_angle_val,
            width=self.entry_width)
        self.cantilever_beam_moment_angle_entry.config(state='readonly')
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_angle_entry)

        self.cantilever_beam_power_list = []

        self.cantilever_beam_power_F_label = tkinter.Label(
            self.root, text="力(单位为N，向下为正方向)=")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_F_label)
        self.cantilever_beam_power_F_val = tkinter.StringVar()
        self.cantilever_beam_power_F_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_F_val,
            width=self.entry_width)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_F_entry)

        self.cantilever_beam_power_E_label = tkinter.Label(
            self.root, text="弹性模量(单位为GPa)=")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_E_label)
        self.cantilever_beam_power_E_val = tkinter.StringVar()
        self.cantilever_beam_power_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_E_val,
            width=self.entry_width)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_E_entry)

        self.cantilever_beam_power_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_I_label)
        self.cantilever_beam_power_I_val = tkinter.StringVar()
        self.cantilever_beam_power_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_I_val,
            width=self.entry_width)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_I_entry)

        self.cantilever_beam_power_l_label = tkinter.Label(self.root,
                                                           text="梁长(单位为m)=")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_l_label)
        self.cantilever_beam_power_l_val = tkinter.StringVar()
        self.cantilever_beam_power_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_l_val,
            width=self.entry_width)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_l_entry)

        self.cantilever_beam_power_button = tkinter.Button(
            self.root, text="确定", command=self.cantilever_beam_power_determine)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_button)

        self.cantilever_beam_power_w_label = tkinter.Label(self.root,
                                                           text="挠度方程(单位为m)：")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_w_label)
        self.cantilever_beam_power_w_val = tkinter.StringVar()
        self.cantilever_beam_power_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_w_val,
            width=self.entry_width)
        self.cantilever_beam_power_w_entry.config(state='readonly')
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_w_entry)

        self.cantilever_beam_power_angle_label = tkinter.Label(
            self.root, text="端截面转角(单位为弧度)：")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_angle_label)
        self.cantilever_beam_power_angle_val = tkinter.StringVar()
        self.cantilever_beam_power_angle_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_angle_val,
            width=self.entry_width)
        self.cantilever_beam_power_angle_entry.config(state='readonly')
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_angle_entry)

        self.root.mainloop()

    def cantilever_beam_moment_interface(self):
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        self.cantilever_beam_moment_M_label.grid(row=0, column=0, sticky='E')
        self.cantilever_beam_moment_M_entry.grid(row=0, column=1, sticky='E')
        self.cantilever_beam_moment_M_val.set("1")
        self.cantilever_beam_moment_E_label.grid(row=1, column=0, sticky='E')
        self.cantilever_beam_moment_E_entry.grid(row=1, column=1, sticky='E')
        self.cantilever_beam_moment_E_val.set("1")
        self.cantilever_beam_moment_I_label.grid(row=2, column=0, sticky='E')
        self.cantilever_beam_moment_I_entry.grid(row=2, column=1, sticky='E')
        self.cantilever_beam_moment_I_val.set("1")
        self.cantilever_beam_moment_l_label.grid(row=3, column=0, sticky='E')
        self.cantilever_beam_moment_l_entry.grid(row=3, column=1, sticky='E')
        self.cantilever_beam_moment_l_val.set("1")
        self.cantilever_beam_moment_button.grid(row=4, column=0, columnspan=2)
        self.cantilever_beam_moment_w_label.grid(row=5, column=0, sticky='E')
        self.cantilever_beam_moment_w_entry.grid(row=5, column=1, sticky='E')
        self.cantilever_beam_moment_w_val.set("")
        self.cantilever_beam_moment_angle_label.grid(row=6,
                                                     column=0,
                                                     sticky='E')
        self.cantilever_beam_moment_angle_entry.grid(row=6,
                                                     column=1,
                                                     sticky='E')
        self.cantilever_beam_moment_angle_val.set("")

    def cantilever_beam_moment_determine(self):
        coefficient_w = -float(self.cantilever_beam_moment_M_entry.get()) / (
            2 * float(self.cantilever_beam_moment_E_entry.get()) * 10**9 *
            float(self.cantilever_beam_moment_I_entry.get()) / 10**8)
        self.cantilever_beam_moment_w_val.set("w=%0.7f*x^(2)" % coefficient_w)
        angle_B = 2 * coefficient_w * float(
            self.cantilever_beam_moment_l_entry.get())
        self.cantilever_beam_moment_angle_val.set("%0.7f " % angle_B)

    def cantilever_beam_power_interface(self):
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        self.cantilever_beam_power_F_label.grid(row=0, column=0, sticky='E')
        self.cantilever_beam_power_F_entry.grid(row=0, column=1, sticky='E')
        self.cantilever_beam_power_F_val.set("1")
        self.cantilever_beam_power_E_label.grid(row=1, column=0, sticky='E')
        self.cantilever_beam_power_E_entry.grid(row=1, column=1, sticky='E')
        self.cantilever_beam_power_E_val.set("1")
        self.cantilever_beam_power_I_label.grid(row=2, column=0, sticky='E')
        self.cantilever_beam_power_I_entry.grid(row=2, column=1, sticky='E')
        self.cantilever_beam_power_I_val.set("1")
        self.cantilever_beam_power_l_label.grid(row=3, column=0, sticky='E')
        self.cantilever_beam_power_l_entry.grid(row=3, column=1, sticky='E')
        self.cantilever_beam_power_l_val.set("1")
        self.cantilever_beam_power_button.grid(row=4, column=0, columnspan=2)
        self.cantilever_beam_power_w_label.grid(row=5, column=0, sticky='E')
        self.cantilever_beam_power_w_entry.grid(row=5, column=1, sticky='E')
        self.cantilever_beam_power_w_val.set("")
        self.cantilever_beam_power_angle_label.grid(row=6,
                                                    column=0,
                                                    sticky='E')
        self.cantilever_beam_power_angle_entry.grid(row=6,
                                                    column=1,
                                                    sticky='E')
        self.cantilever_beam_power_angle_val.set("")

    def cantilever_beam_power_determine(self):
        coefficient_w = -float(self.cantilever_beam_power_F_entry.get()) / (
            6 * float(self.cantilever_beam_power_E_entry.get()) * 10**9 *
            float(self.cantilever_beam_power_I_entry.get()) / 10**8)
        intercept = 3 * float(self.cantilever_beam_power_l_entry.get())
        self.cantilever_beam_power_w_val.set("w=%0.7f*x^(2)*(%0.2f-x)" %
                                             (coefficient_w, intercept))
        angle_B = 3 * coefficient_w * float(
            self.cantilever_beam_power_l_entry.get())**2
        self.cantilever_beam_power_angle_val.set("%0.7f " % angle_B)

    def course(self):
        self.help_top = tkinter.Toplevel()
        self.help_top.title("教程")
        self.help_label = tkinter.Label(
            self.help_top,
            justify="left",
            text="使用步骤如下：\n1.从菜单栏中选择梁的种类和受力类型；\n2.输入受\
力值、弹性模量、惯性矩等参数；\n3.点击确定按钮，从下面文本框读取挠度方程和端截面转\
角。\n注：\n1.此处仅可以计算悬臂梁和简支梁模型，外伸梁可以基于这两种情况用叠加法计\
算；\n2.由于此处解算进行了对称弯曲假设和纯弯曲假设，计算结果仅适用于横截面关于剪力\
方向对称的细长梁；\n3.此处仅计算受力点在自由端或全梁受分布载荷等最基本情况，其他情\
况可以根据端截面转角或叠加法方便地算出。")
        self.help_label.pack()

    def about(self):
        self.about_top = tkinter.Toplevel()
        self.about_top.geometry("200x100")
        self.about_top.title("关于")
        self.about_label = tkinter.Label(self.about_top,
                                         justify="left",
                                         text="弯矩方程计算器\n版本号：0.0.1\n\
权利声明：xxxxxx\n网址：xxxxxx")
        self.about_label.pack()


d = deflectionEquationCalculator()
