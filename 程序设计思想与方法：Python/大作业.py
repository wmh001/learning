# -*-coding:utf-8-*-

# 导入模块
import tkinter


# 挠度方程求解
class deflectionEquationSolution:
    def __init__(self):
        # 创建根窗口
        self.root = tkinter.Tk()
        self.root.title("弯矩方程求解")

        # 定义宽度常数
        self.entry_width = 50
        self.label_width = 40
        self.canvas_width = 314

        # 创建菜单系统
        self.meun = tkinter.Menu(self.root)
        self.root.config(menu=self.meun)
        self.beam_type_meun = tkinter.Menu(self.meun)
        self.cantilever_beam_type_meun = tkinter.Menu(self.beam_type_meun)
        self.simple_beam_type_meun = tkinter.Menu(self.beam_type_meun)
        self.help_meun = tkinter.Menu(self.root)
        self.meun.add_cascade(label="梁的种类", menu=self.beam_type_meun)
        self.beam_type_meun.add_cascade(label="悬臂梁",
                                        menu=self.cantilever_beam_type_meun)
        self.cantilever_beam_type_meun.add_command(
            label="受端力矩", command=self.cantilever_beam_moment_interface)
        self.cantilever_beam_type_meun.add_command(
            label="受端力", command=self.cantilever_beam_power_interface)
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
                                          width=68,
                                          text="欢迎使用！\n请在上面菜单栏中选择梁的种类或获取帮助。")
        self.initial_text.config(font=("宋体", 20))
        self.initial_text.pack()

        # 创建受力矩悬臂梁的构件
        # 创建力矩悬臂梁构件列表
        self.cantilever_beam_moment_list = []

        # 创建力矩输入口
        self.cantilever_beam_moment_M_label = tkinter.Label(
            self.root,
            text="力矩(单位为N*m，顺时针为正方向)=",
            width=self.label_width,
            anchor='e')
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_M_label)
        self.cantilever_beam_moment_M_val = tkinter.StringVar()
        self.cantilever_beam_moment_M_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_M_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_M_entry)

        # 创建弹性模量输入口
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

        # 创建惯性矩输入口
        self.cantilever_beam_moment_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_I_label)
        self.cantilever_beam_moment_I_val = tkinter.StringVar()
        self.cantilever_beam_moment_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_moment_I_val,
            width=self.entry_width)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_I_entry)

        # 创建梁长输入口
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

        # 创建确定按钮
        self.cantilever_beam_moment_button = tkinter.Button(
            self.root,
            text="确定",
            command=self.cantilever_beam_moment_determine)
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_button)

        # 创建挠度方程输出口
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

        # 创建端截面转角输出口
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

        # 创建示意图
        self.cantilever_beam_moment_canvas = tkinter.Canvas(
            self.root, width=self.canvas_width, height=161, bg="white")
        self.cantilever_beam_moment_list.append(
            self.cantilever_beam_moment_canvas)

        # 创建受力悬臂梁的构件
        # 创建力悬臂梁构件列表
        self.cantilever_beam_power_list = []

        # 创建力输入口
        self.cantilever_beam_power_F_label = tkinter.Label(
            self.root,
            text="力(单位为N，向下为正方向)=",
            width=self.label_width,
            anchor='e')
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_F_label)
        self.cantilever_beam_power_F_val = tkinter.StringVar()
        self.cantilever_beam_power_F_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_power_F_val,
            width=self.entry_width)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_F_entry)

        # 创建弹性模量输入口
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

        # 创建惯性矩输入口
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

        # 创建梁长输入口
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

        # 创建确定按钮
        self.cantilever_beam_power_button = tkinter.Button(
            self.root, text="确定", command=self.cantilever_beam_power_determine)
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_button)

        # 创建挠度方程输出口
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

        # 创建端截面转角输出口
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

        # 创建示意图
        self.cantilever_beam_power_canvas = tkinter.Canvas(
            self.root, width=self.canvas_width, height=161, bg="white")
        self.cantilever_beam_power_list.append(
            self.cantilever_beam_power_canvas)

        # 创建受均布载荷悬臂梁的构件
        # 创建均布载荷悬臂梁构件列表
        self.cantilever_beam_UL_list = []

        # 创建集度输入口
        self.cantilever_beam_UL_q_label = tkinter.Label(
            self.root,
            text="均布载荷集度(单位为N*m^(-1))，向下为正方向)=",
            width=self.label_width,
            anchor='e')
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_q_label)
        self.cantilever_beam_UL_q_val = tkinter.StringVar()
        self.cantilever_beam_UL_q_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_q_val,
            width=self.entry_width)
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_q_entry)

        # 创建弹性模量输入口
        self.cantilever_beam_UL_E_label = tkinter.Label(self.root,
                                                        text="弹性模量(单位为GPa)=")
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_E_label)
        self.cantilever_beam_UL_E_val = tkinter.StringVar()
        self.cantilever_beam_UL_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_E_val,
            width=self.entry_width)
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_E_entry)

        # 创建惯性矩输入口
        self.cantilever_beam_UL_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_I_label)
        self.cantilever_beam_UL_I_val = tkinter.StringVar()
        self.cantilever_beam_UL_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_I_val,
            width=self.entry_width)
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_I_entry)

        # 创建梁长输入口
        self.cantilever_beam_UL_l_label = tkinter.Label(self.root,
                                                        text="梁长(单位为m)=")
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_l_label)
        self.cantilever_beam_UL_l_val = tkinter.StringVar()
        self.cantilever_beam_UL_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_l_val,
            width=self.entry_width)
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_l_entry)

        # 创建确定按钮
        self.cantilever_beam_UL_button = tkinter.Button(
            self.root, text="确定", command=self.cantilever_beam_UL_determine)
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_button)

        # 创建挠度方程输出口
        self.cantilever_beam_UL_w_label = tkinter.Label(self.root,
                                                        text="挠度方程(单位为m)：")
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_w_label)
        self.cantilever_beam_UL_w_val = tkinter.StringVar()
        self.cantilever_beam_UL_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_w_val,
            width=self.entry_width)
        self.cantilever_beam_UL_w_entry.config(state='readonly')
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_w_entry)

        # 创建端截面转角输出口
        self.cantilever_beam_UL_angle_label = tkinter.Label(
            self.root, text="端截面转角(单位为弧度)：")
        self.cantilever_beam_UL_list.append(
            self.cantilever_beam_UL_angle_label)
        self.cantilever_beam_UL_angle_val = tkinter.StringVar()
        self.cantilever_beam_UL_angle_entry = tkinter.Entry(
            self.root,
            textvariable=self.cantilever_beam_UL_angle_val,
            width=self.entry_width)
        self.cantilever_beam_UL_angle_entry.config(state='readonly')
        self.cantilever_beam_UL_list.append(
            self.cantilever_beam_UL_angle_entry)

        # 创建示意图
        self.cantilever_beam_UL_canvas = tkinter.Canvas(
            self.root, width=self.canvas_width, height=161, bg="white")
        self.cantilever_beam_UL_list.append(self.cantilever_beam_UL_canvas)

        # 创建受力矩简支梁的构件
        # 创建力矩简支梁构件列表
        self.simple_beam_moment_list = []

        # 创建力矩输入口
        self.simple_beam_moment_M_label = tkinter.Label(
            self.root,
            text="力矩(单位为N*m，顺时针为正方向)=",
            width=self.label_width,
            anchor='e')
        self.simple_beam_moment_list.append(self.simple_beam_moment_M_label)
        self.simple_beam_moment_M_val = tkinter.StringVar()
        self.simple_beam_moment_M_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_M_val,
            width=self.entry_width)
        self.simple_beam_moment_list.append(self.simple_beam_moment_M_entry)

        # 创建弹性模量输入口
        self.simple_beam_moment_E_label = tkinter.Label(self.root,
                                                        text="弹性模量(单位为GPa)=")
        self.simple_beam_moment_list.append(self.simple_beam_moment_E_label)
        self.simple_beam_moment_E_val = tkinter.StringVar()
        self.simple_beam_moment_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_E_val,
            width=self.entry_width)
        self.simple_beam_moment_list.append(self.simple_beam_moment_E_entry)

        # 创建惯性矩输入口
        self.simple_beam_moment_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.simple_beam_moment_list.append(self.simple_beam_moment_I_label)
        self.simple_beam_moment_I_val = tkinter.StringVar()
        self.simple_beam_moment_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_I_val,
            width=self.entry_width)
        self.simple_beam_moment_list.append(self.simple_beam_moment_I_entry)

        # 创建梁长输入口
        self.simple_beam_moment_l_label = tkinter.Label(self.root,
                                                        text="梁长(单位为m)=")
        self.simple_beam_moment_list.append(self.simple_beam_moment_l_label)
        self.simple_beam_moment_l_val = tkinter.StringVar()
        self.simple_beam_moment_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_l_val,
            width=self.entry_width)
        self.simple_beam_moment_list.append(self.simple_beam_moment_l_entry)

        # 创建力端距输入口
        self.simple_beam_moment_a_label = tkinter.Label(
            self.root, text="受力点到左端的距离(单位为m)=")
        self.simple_beam_moment_list.append(self.simple_beam_moment_a_label)
        self.simple_beam_moment_a_val = tkinter.StringVar()
        self.simple_beam_moment_a_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_a_val,
            width=self.entry_width)
        self.simple_beam_moment_list.append(self.simple_beam_moment_a_entry)

        # 创建确定按钮
        self.simple_beam_moment_button = tkinter.Button(
            self.root, text="确定", command=self.simple_beam_moment_determine)
        self.simple_beam_moment_list.append(self.simple_beam_moment_button)

        # 创建挠度方程输出口
        self.simple_beam_moment_w_label = tkinter.Label(self.root,
                                                        text="挠度方程(单位为m)：")
        self.simple_beam_moment_list.append(self.simple_beam_moment_w_label)
        self.simple_beam_moment_w_val = tkinter.StringVar()
        self.simple_beam_moment_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_w_val,
            width=self.entry_width)
        self.simple_beam_moment_w_entry.config(state='readonly')
        self.simple_beam_moment_list.append(self.simple_beam_moment_w_entry)
        self.simple_beam_moment_w_val2 = tkinter.StringVar()
        self.simple_beam_moment_w_entry2 = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_w_val2,
            width=self.entry_width)
        self.simple_beam_moment_w_entry2.config(state='readonly')
        self.simple_beam_moment_list.append(self.simple_beam_moment_w_entry2)

        # 创建左端截面转角
        self.simple_beam_moment_angleA_label = tkinter.Label(
            self.root, text="左端截面转角(单位为弧度)：")
        self.simple_beam_moment_list.append(
            self.simple_beam_moment_angleA_label)
        self.simple_beam_moment_angleA_val = tkinter.StringVar()
        self.simple_beam_moment_angleA_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_angleA_val,
            width=self.entry_width)
        self.simple_beam_moment_angleA_entry.config(state='readonly')
        self.simple_beam_moment_list.append(
            self.simple_beam_moment_angleA_entry)

        # 创建右端截面转角
        self.simple_beam_moment_angleB_label = tkinter.Label(
            self.root, text="右端截面转角(单位为弧度)：")
        self.simple_beam_moment_list.append(
            self.simple_beam_moment_angleB_label)
        self.simple_beam_moment_angleB_val = tkinter.StringVar()
        self.simple_beam_moment_angleB_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_moment_angleB_val,
            width=self.entry_width)
        self.simple_beam_moment_angleB_entry.config(state='readonly')
        self.simple_beam_moment_list.append(
            self.simple_beam_moment_angleB_entry)

        # 创建示意图
        self.simple_beam_moment_canvas = tkinter.Canvas(
            self.root, width=self.canvas_width, height=161, bg="white")
        self.simple_beam_moment_list.append(self.simple_beam_moment_canvas)

        # 创建受力简支梁的构件
        # 创建力简支梁构件列表
        self.simple_beam_power_list = []

        # 创建力输入口
        self.simple_beam_power_F_label = tkinter.Label(self.root,
                                                       text="力(单位为N，向下为正方向)=",
                                                       width=self.label_width,
                                                       anchor='e')
        self.simple_beam_power_list.append(self.simple_beam_power_F_label)
        self.simple_beam_power_F_val = tkinter.StringVar()
        self.simple_beam_power_F_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_F_val,
            width=self.entry_width)
        self.simple_beam_power_list.append(self.simple_beam_power_F_entry)

        # 创建弹性模量输入口
        self.simple_beam_power_E_label = tkinter.Label(self.root,
                                                       text="弹性模量(单位为GPa)=")
        self.simple_beam_power_list.append(self.simple_beam_power_E_label)
        self.simple_beam_power_E_val = tkinter.StringVar()
        self.simple_beam_power_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_E_val,
            width=self.entry_width)
        self.simple_beam_power_list.append(self.simple_beam_power_E_entry)

        # 创建惯性矩输入口
        self.simple_beam_power_I_label = tkinter.Label(
            self.root, text="关于中性轴的惯性矩(单位为cm^4)=")
        self.simple_beam_power_list.append(self.simple_beam_power_I_label)
        self.simple_beam_power_I_val = tkinter.StringVar()
        self.simple_beam_power_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_I_val,
            width=self.entry_width)
        self.simple_beam_power_list.append(self.simple_beam_power_I_entry)

        # 创建梁长输入口
        self.simple_beam_power_l_label = tkinter.Label(self.root,
                                                       text="梁长(单位为m)=")
        self.simple_beam_power_list.append(self.simple_beam_power_l_label)
        self.simple_beam_power_l_val = tkinter.StringVar()
        self.simple_beam_power_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_l_val,
            width=self.entry_width)
        self.simple_beam_power_list.append(self.simple_beam_power_l_entry)

        # 创建力端距输入口
        self.simple_beam_power_a_label = tkinter.Label(self.root,
                                                       text="受力点到左端的距离(单位为m)=")
        self.simple_beam_power_list.append(self.simple_beam_power_a_label)
        self.simple_beam_power_a_val = tkinter.StringVar()
        self.simple_beam_power_a_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_a_val,
            width=self.entry_width)
        self.simple_beam_power_list.append(self.simple_beam_power_a_entry)

        # 创建确定按钮
        self.simple_beam_power_button = tkinter.Button(
            self.root, text="确定", command=self.simple_beam_power_determine)
        self.simple_beam_power_list.append(self.simple_beam_power_button)

        # 创建挠度方程输出口
        self.simple_beam_power_w_label = tkinter.Label(self.root,
                                                       text="挠度方程(单位为m)：")
        self.simple_beam_power_list.append(self.simple_beam_power_w_label)
        self.simple_beam_power_w_val = tkinter.StringVar()
        self.simple_beam_power_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_w_val,
            width=self.entry_width)
        self.simple_beam_power_w_entry.config(state='readonly')
        self.simple_beam_power_list.append(self.simple_beam_power_w_entry)
        self.simple_beam_power_w_val2 = tkinter.StringVar()
        self.simple_beam_power_w_entry2 = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_w_val2,
            width=self.entry_width)
        self.simple_beam_power_w_entry2.config(state='readonly')
        self.simple_beam_power_list.append(self.simple_beam_power_w_entry2)

        # 创建左端截面转角
        self.simple_beam_power_angleA_label = tkinter.Label(
            self.root, text="左端截面转角(单位为弧度)：")
        self.simple_beam_power_list.append(self.simple_beam_power_angleA_label)
        self.simple_beam_power_angleA_val = tkinter.StringVar()
        self.simple_beam_power_angleA_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_angleA_val,
            width=self.entry_width)
        self.simple_beam_power_angleA_entry.config(state='readonly')
        self.simple_beam_power_list.append(self.simple_beam_power_angleA_entry)

        # 创建右端截面转角
        self.simple_beam_power_angleB_label = tkinter.Label(
            self.root, text="右端截面转角(单位为弧度)：")
        self.simple_beam_power_list.append(self.simple_beam_power_angleB_label)
        self.simple_beam_power_angleB_val = tkinter.StringVar()
        self.simple_beam_power_angleB_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_power_angleB_val,
            width=self.entry_width)
        self.simple_beam_power_angleB_entry.config(state='readonly')
        self.simple_beam_power_list.append(self.simple_beam_power_angleB_entry)

        # 创建示意图
        self.simple_beam_power_canvas = tkinter.Canvas(self.root,
                                                       width=self.canvas_width,
                                                       height=161,
                                                       bg="white")
        self.simple_beam_power_list.append(self.simple_beam_power_canvas)

        # 创建受均布载荷简支梁的构件
        # 创建均布载荷简支梁构件列表
        self.simple_beam_UL_list = []

        # 创建集度输入口
        self.simple_beam_UL_q_label = tkinter.Label(
            self.root,
            text="均布载荷集度(单位为N*m^(-1))，向下为正方向)=",
            width=self.label_width,
            anchor='e')
        self.simple_beam_UL_list.append(self.simple_beam_UL_q_label)
        self.simple_beam_UL_q_val = tkinter.StringVar()
        self.simple_beam_UL_q_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_q_val,
            width=self.entry_width)
        self.simple_beam_UL_list.append(self.simple_beam_UL_q_entry)

        # 创建弹性模量输入口
        self.simple_beam_UL_E_label = tkinter.Label(self.root,
                                                    text="弹性模量(单位为GPa)=")
        self.simple_beam_UL_list.append(self.simple_beam_UL_E_label)
        self.simple_beam_UL_E_val = tkinter.StringVar()
        self.simple_beam_UL_E_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_E_val,
            width=self.entry_width)
        self.simple_beam_UL_list.append(self.simple_beam_UL_E_entry)

        # 创建惯性矩输入口
        self.simple_beam_UL_I_label = tkinter.Label(self.root,
                                                    text="关于中性轴的惯性矩(单位为cm^4)=")
        self.simple_beam_UL_list.append(self.simple_beam_UL_I_label)
        self.simple_beam_UL_I_val = tkinter.StringVar()
        self.simple_beam_UL_I_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_I_val,
            width=self.entry_width)
        self.simple_beam_UL_list.append(self.simple_beam_UL_I_entry)

        # 创建梁长输入口
        self.simple_beam_UL_l_label = tkinter.Label(self.root,
                                                    text="梁长(单位为m)=")
        self.simple_beam_UL_list.append(self.simple_beam_UL_l_label)
        self.simple_beam_UL_l_val = tkinter.StringVar()
        self.simple_beam_UL_l_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_l_val,
            width=self.entry_width)
        self.simple_beam_UL_list.append(self.simple_beam_UL_l_entry)

        # 创建确定按钮
        self.simple_beam_UL_button = tkinter.Button(
            self.root, text="确定", command=self.simple_beam_UL_determine)
        self.simple_beam_UL_list.append(self.simple_beam_UL_button)

        # 创建挠度方程输出口
        self.simple_beam_UL_w_label = tkinter.Label(self.root,
                                                    text="挠度方程(单位为m)：")
        self.simple_beam_UL_list.append(self.simple_beam_UL_w_label)
        self.simple_beam_UL_w_val = tkinter.StringVar()
        self.simple_beam_UL_w_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_w_val,
            width=self.entry_width)
        self.simple_beam_UL_w_entry.config(state='readonly')
        self.simple_beam_UL_list.append(self.simple_beam_UL_w_entry)

        # 创建左端截面转角
        self.simple_beam_UL_angleA_label = tkinter.Label(self.root,
                                                         text="左端截面转角(单位为弧度)：")
        self.simple_beam_UL_list.append(self.simple_beam_UL_angleA_label)
        self.simple_beam_UL_angleA_val = tkinter.StringVar()
        self.simple_beam_UL_angleA_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_angleA_val,
            width=self.entry_width)
        self.simple_beam_UL_angleA_entry.config(state='readonly')
        self.simple_beam_UL_list.append(self.simple_beam_UL_angleA_entry)

        # 创建右端截面转角
        self.simple_beam_UL_angleB_label = tkinter.Label(self.root,
                                                         text="右端截面转角(单位为弧度)：")
        self.simple_beam_UL_list.append(self.simple_beam_UL_angleB_label)
        self.simple_beam_UL_angleB_val = tkinter.StringVar()
        self.simple_beam_UL_angleB_entry = tkinter.Entry(
            self.root,
            textvariable=self.simple_beam_UL_angleB_val,
            width=self.entry_width)
        self.simple_beam_UL_angleB_entry.config(state='readonly')
        self.simple_beam_UL_list.append(self.simple_beam_UL_angleB_entry)

        # 创建示意图
        self.simple_beam_UL_canvas = tkinter.Canvas(self.root,
                                                    width=self.canvas_width,
                                                    height=161,
                                                    bg="white")
        self.simple_beam_UL_list.append(self.simple_beam_UL_canvas)

        self.root.mainloop()

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

    def warning(self):
        # 创建错误警告窗口
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
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        for i in self.cantilever_beam_UL_list:
            i.grid_forget()
        for i in self.simple_beam_moment_list:
            i.grid_forget()
        for i in self.simple_beam_power_list:
            i.grid_forget()
        for i in self.simple_beam_UL_list:
            i.grid_forget()
        # 布局组件
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
        self.cantilever_beam_moment_canvas.grid(row=0, column=2, rowspan=7)
        self.cantilever_beam_moment_canvas.delete("all")
        self.cantilever_beam_moment_canvas.create_text(150,
                                                       160,
                                                       text="示意图",
                                                       anchor='s')

    # 显示力矩悬臂梁计算结果
    def cantilever_beam_moment_determine(self):
        try:
            # 清除输出口
            self.cantilever_beam_moment_canvas.delete("all")
            self.cantilever_beam_moment_canvas.create_text(150,
                                                           160,
                                                           text="示意图",
                                                           anchor='s')
            # 计算参数
            coefficient_w = -float(self.cantilever_beam_moment_M_entry.get(
            )) / (2 * float(self.cantilever_beam_moment_E_entry.get()) * 10**9
                  * float(self.cantilever_beam_moment_I_entry.get()) / 10**8)
            angle_B = 2 * coefficient_w * float(
                self.cantilever_beam_moment_l_entry.get())
            # 显示结果
            self.cantilever_beam_moment_w_val.set("w=%0.7f*x^(2)" %
                                                  coefficient_w)
            self.cantilever_beam_moment_angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.cantilever_beam_moment_canvas, 50,
                                      80)
            self.draw_moment(self.cantilever_beam_moment_canvas, 250, 80,
                             self.cantilever_beam_moment_M_entry.get())
        except:
            self.warning()

    # 布局力悬臂梁界面
    def cantilever_beam_power_interface(self):
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        for i in self.cantilever_beam_UL_list:
            i.grid_forget()
        for i in self.simple_beam_moment_list:
            i.grid_forget()
        for i in self.simple_beam_power_list:
            i.grid_forget()
        for i in self.simple_beam_UL_list:
            i.grid_forget()
        # 布局组件
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
        self.cantilever_beam_power_canvas.grid(row=0, column=2, rowspan=7)
        self.cantilever_beam_power_canvas.delete("all")
        self.cantilever_beam_power_canvas.create_text(150,
                                                      160,
                                                      text="示意图",
                                                      anchor='s')

    # 显示力悬臂梁计算结果
    def cantilever_beam_power_determine(self):
        try:
            # 清除输出口
            self.cantilever_beam_power_canvas.delete("all")
            self.cantilever_beam_power_canvas.create_text(150,
                                                          160,
                                                          text="示意图",
                                                          anchor='s')
            # 计算参数
            coefficient_w = -float(self.cantilever_beam_power_F_entry.get(
            )) / (6 * float(self.cantilever_beam_power_E_entry.get()) * 10**9 *
                  float(self.cantilever_beam_power_I_entry.get()) / 10**8)
            intercept = 3 * float(self.cantilever_beam_power_l_entry.get())
            angle_B = 3 * coefficient_w * float(
                self.cantilever_beam_power_l_entry.get())**2
            # 显示结果
            self.cantilever_beam_power_w_val.set("w=%0.7f*x^(2)*(%0.2f-x)" %
                                                 (coefficient_w, intercept))
            self.cantilever_beam_power_angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.cantilever_beam_power_canvas, 50,
                                      80)
            self.draw_power(self.cantilever_beam_power_canvas, 250, 80,
                            self.cantilever_beam_power_F_entry.get())
        except:
            self.warning()

    # 布局均布载荷悬臂梁界面
    def cantilever_beam_UL_interface(self):
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        for i in self.simple_beam_moment_list:
            i.grid_forget()
        for i in self.simple_beam_power_list:
            i.grid_forget()
        for i in self.simple_beam_UL_list:
            i.grid_forget()
        # 布局组件
        self.cantilever_beam_UL_q_label.grid(row=0, column=0, sticky='E')
        self.cantilever_beam_UL_q_entry.grid(row=0, column=1, sticky='E')
        self.cantilever_beam_UL_q_val.set("1")
        self.cantilever_beam_UL_E_label.grid(row=1, column=0, sticky='E')
        self.cantilever_beam_UL_E_entry.grid(row=1, column=1, sticky='E')
        self.cantilever_beam_UL_E_val.set("1")
        self.cantilever_beam_UL_I_label.grid(row=2, column=0, sticky='E')
        self.cantilever_beam_UL_I_entry.grid(row=2, column=1, sticky='E')
        self.cantilever_beam_UL_I_val.set("1")
        self.cantilever_beam_UL_l_label.grid(row=3, column=0, sticky='E')
        self.cantilever_beam_UL_l_entry.grid(row=3, column=1, sticky='E')
        self.cantilever_beam_UL_l_val.set("1")
        self.cantilever_beam_UL_button.grid(row=4, column=0, columnspan=2)
        self.cantilever_beam_UL_w_label.grid(row=5, column=0, sticky='E')
        self.cantilever_beam_UL_w_entry.grid(row=5, column=1, sticky='E')
        self.cantilever_beam_UL_w_val.set("")
        self.cantilever_beam_UL_angle_label.grid(row=6, column=0, sticky='E')
        self.cantilever_beam_UL_angle_entry.grid(row=6, column=1, sticky='E')
        self.cantilever_beam_UL_angle_val.set("")
        self.cantilever_beam_UL_canvas.grid(row=0, column=2, rowspan=7)
        self.cantilever_beam_UL_canvas.delete("all")
        self.cantilever_beam_UL_canvas.create_text(150,
                                                   160,
                                                   text="示意图",
                                                   anchor='s')

    # 显示均布载荷悬臂梁计算结果
    def cantilever_beam_UL_determine(self):
        try:
            # 清除输出口
            self.cantilever_beam_UL_canvas.delete("all")
            self.cantilever_beam_UL_canvas.create_text(150,
                                                       160,
                                                       text="示意图",
                                                       anchor='s')
            # 计算参数
            coefficient_w = -float(self.cantilever_beam_UL_q_entry.get()) / (
                24 * float(self.cantilever_beam_UL_E_entry.get()) * 10**9 *
                float(self.cantilever_beam_UL_I_entry.get()) / 10**8)
            coefficient_x = -4 * float(self.cantilever_beam_UL_l_entry.get())
            intercept = 6 * float(self.cantilever_beam_UL_l_entry.get())**2
            angle_B = 4 * coefficient_w * float(
                self.cantilever_beam_UL_l_entry.get())**3
            # 显示结果
            self.cantilever_beam_UL_w_val.set(
                "w=%0.7f*x^(2)*(x^2%0.2f*x+%0.2f)" %
                (coefficient_w, coefficient_x, intercept))
            self.cantilever_beam_UL_angle_val.set("%0.7f " % angle_B)
            # 绘制示意图
            self.draw_cantilever_beam(self.cantilever_beam_UL_canvas, 50, 80)
            self.draw_UL(self.cantilever_beam_UL_canvas, 50, 80,
                         self.cantilever_beam_UL_q_entry.get())
        except:
            self.warning()

    # 布局力矩简支梁界面
    def simple_beam_moment_interface(self):
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        for i in self.cantilever_beam_UL_list:
            i.grid_forget()
        for i in self.simple_beam_power_list:
            i.grid_forget()
        for i in self.simple_beam_UL_list:
            i.grid_forget()
        # 布局组件
        self.simple_beam_moment_M_label.grid(row=0, column=0, sticky='E')
        self.simple_beam_moment_M_entry.grid(row=0, column=1, sticky='E')
        self.simple_beam_moment_M_val.set("1")
        self.simple_beam_moment_E_label.grid(row=1, column=0, sticky='E')
        self.simple_beam_moment_E_entry.grid(row=1, column=1, sticky='E')
        self.simple_beam_moment_E_val.set("1")
        self.simple_beam_moment_I_label.grid(row=2, column=0, sticky='E')
        self.simple_beam_moment_I_entry.grid(row=2, column=1, sticky='E')
        self.simple_beam_moment_I_val.set("1")
        self.simple_beam_moment_l_label.grid(row=3, column=0, sticky='E')
        self.simple_beam_moment_l_entry.grid(row=3, column=1, sticky='E')
        self.simple_beam_moment_l_val.set("1")
        self.simple_beam_moment_a_label.grid(row=4, column=0, sticky='E')
        self.simple_beam_moment_a_entry.grid(row=4, column=1, sticky='E')
        self.simple_beam_moment_a_val.set("1")
        self.simple_beam_moment_button.grid(row=5, column=0, columnspan=2)
        self.simple_beam_moment_w_label.grid(row=6, column=0, sticky='E')
        self.simple_beam_moment_w_entry.grid(row=6, column=1, sticky='E')
        self.simple_beam_moment_w_val.set("")
        self.simple_beam_moment_w_entry2.grid(row=7, column=1, sticky='E')
        self.simple_beam_moment_w_val2.set("")
        self.simple_beam_moment_angleA_label.grid(row=8, column=0, sticky='E')
        self.simple_beam_moment_angleA_entry.grid(row=8, column=1, sticky='E')
        self.simple_beam_moment_angleA_val.set("")
        self.simple_beam_moment_angleB_label.grid(row=9, column=0, sticky='E')
        self.simple_beam_moment_angleB_entry.grid(row=9, column=1, sticky='E')
        self.simple_beam_moment_angleB_val.set("")
        self.simple_beam_moment_canvas.grid(row=0, column=2, rowspan=7)
        self.simple_beam_moment_canvas.delete("all")
        self.simple_beam_moment_canvas.create_text(150,
                                                   160,
                                                   text="示意图",
                                                   anchor='s')

    # 显示力矩简支梁计算结果
    def simple_beam_moment_determine(self):
        try:
            # 清除输出口
            self.simple_beam_moment_canvas.delete("all")
            self.simple_beam_moment_canvas.create_text(150,
                                                       160,
                                                       text="示意图",
                                                       anchor='s')
            # 计算参数
            L = float(self.simple_beam_moment_l_entry.get())
            a = float(self.simple_beam_moment_a_entry.get())
            b = L - a
            # 力端距大于梁长报错
            if a > L:
                self.warning()
                return
            coefficient_w = float(self.simple_beam_moment_M_entry.get()) / (
                6 * float(self.simple_beam_moment_E_entry.get()) * 10**9 *
                float(self.simple_beam_moment_I_entry.get()) / 10**8 *
                float(self.simple_beam_moment_l_entry.get()))
            angle_A = coefficient_w * (L**2 - 3 * b**2)
            angle_B = coefficient_w * (L**2 - 3 * a**2)
            # 显示结果
            self.simple_beam_moment_angleA_val.set("%0.7f " % angle_A)
            self.simple_beam_moment_angleB_val.set("%0.7f " % angle_B)
            if a == 0:
                self.simple_beam_moment_w_val.set(
                    "w=-%0.7f*x*(%0.2f-x)(%0.2f-x" % (coefficient_w, L, 2 * L))
                self.simple_beam_moment_w_val2.set("-------------------------")
            elif b == 0:
                self.simple_beam_moment_w_val.set("w=%0.7f*x*(%0.2f-x^2)" %
                                                  (coefficient_w, L**2))
                self.simple_beam_moment_w_val2.set("-------------------------")
            else:
                self.simple_beam_moment_w_val.set(
                    "w=%0.7f*x*(%0.2f-x^2)(0≤x≤%0.2f)" %
                    (coefficient_w, L**2 - 3 * b**2, a))
                self.simple_beam_moment_w_val2.set(
                    "w=%0.7f*(-x^3+%0.2f*(x-%0.2f)^2+%0.2f*x)(%0.2f≤x≤%0.2f)" %
                    (coefficient_w, 3 * L, a, L**2 - 3 * b**2, a, L))
            # 绘制示意图
            self.draw_simple_beam(self.simple_beam_moment_canvas, 50, 80)
            self.draw_moment(self.simple_beam_moment_canvas, 50 + 200 * a / L,
                             80, self.simple_beam_moment_M_entry.get())
        except:
            self.warning()

    # 布局力简支梁界面
    def simple_beam_power_interface(self):
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        for i in self.cantilever_beam_UL_list:
            i.grid_forget()
        for i in self.simple_beam_moment_list:
            i.grid_forget()
        for i in self.simple_beam_UL_list:
            i.grid_forget()
        # 布局组件
        self.simple_beam_power_F_label.grid(row=0, column=0, sticky='E')
        self.simple_beam_power_F_entry.grid(row=0, column=1, sticky='E')
        self.simple_beam_power_F_val.set("1")
        self.simple_beam_power_E_label.grid(row=1, column=0, sticky='E')
        self.simple_beam_power_E_entry.grid(row=1, column=1, sticky='E')
        self.simple_beam_power_E_val.set("1")
        self.simple_beam_power_I_label.grid(row=2, column=0, sticky='E')
        self.simple_beam_power_I_entry.grid(row=2, column=1, sticky='E')
        self.simple_beam_power_I_val.set("1")
        self.simple_beam_power_l_label.grid(row=3, column=0, sticky='E')
        self.simple_beam_power_l_entry.grid(row=3, column=1, sticky='E')
        self.simple_beam_power_l_val.set("1")
        self.simple_beam_power_a_label.grid(row=4, column=0, sticky='E')
        self.simple_beam_power_a_entry.grid(row=4, column=1, sticky='E')
        self.simple_beam_power_a_val.set("1")
        self.simple_beam_power_button.grid(row=5, column=0, columnspan=2)
        self.simple_beam_power_w_label.grid(row=6, column=0, sticky='E')
        self.simple_beam_power_w_entry.grid(row=6, column=1, sticky='E')
        self.simple_beam_power_w_val.set("")
        self.simple_beam_power_w_entry2.grid(row=7, column=1, sticky='E')
        self.simple_beam_power_w_val2.set("")
        self.simple_beam_power_angleA_label.grid(row=8, column=0, sticky='E')
        self.simple_beam_power_angleA_entry.grid(row=8, column=1, sticky='E')
        self.simple_beam_power_angleA_val.set("")
        self.simple_beam_power_angleB_label.grid(row=9, column=0, sticky='E')
        self.simple_beam_power_angleB_entry.grid(row=9, column=1, sticky='E')
        self.simple_beam_power_angleB_val.set("")
        self.simple_beam_power_canvas.grid(row=0, column=2, rowspan=7)
        self.simple_beam_power_canvas.delete("all")
        self.simple_beam_power_canvas.create_text(150,
                                                  160,
                                                  text="示意图",
                                                  anchor='s')

    # 显示力简支梁计算结果
    def simple_beam_power_determine(self):
        try:
            # 清除输出口
            self.simple_beam_power_canvas.delete("all")
            self.simple_beam_power_canvas.create_text(150,
                                                      160,
                                                      text="示意图",
                                                      anchor='s')
            # 计算参数
            L = float(self.simple_beam_power_l_entry.get())
            a = float(self.simple_beam_power_a_entry.get())
            b = L - a
            # 力端距大于梁长报错
            if a > L:
                self.warning()
                return
            coefficient_w = -float(
                self.simple_beam_power_F_entry.get()) * b / (
                    6 * float(self.simple_beam_power_E_entry.get()) * 10**9 *
                    float(self.simple_beam_power_I_entry.get()) / 10**8 * L)
            angle_A = coefficient_w * a * (L + b)
            angle_B = -coefficient_w * a * (L + a)
            # 显示结果
            self.simple_beam_power_angleA_val.set("%0.7f " % angle_A)
            self.simple_beam_power_angleB_val.set("%0.7f " % angle_B)
            if a == 0:
                self.simple_beam_power_w_val.set("w=0")
                self.simple_beam_power_w_val2.set("-------------------------")
            elif b == 0:
                self.simple_beam_power_w_val.set("w=0")
                self.simple_beam_power_w_val2.set("-------------------------")
            else:
                self.simple_beam_power_w_val.set(
                    "w=%0.7f*x*(%0.2f-x^2)(0≤x≤%0.2f)" %
                    (coefficient_w, L**2 - b**2, a))
                self.simple_beam_power_w_val2.set(
                    "w=%0.7f*(%0.2f(x-%0.2f)^3+%0.2f*x-x^3)(%0.2f≤x≤%0.2f)" %
                    (coefficient_w, L / b, a, L**2 - b**2, a, L))
            # 绘制示意图
            self.draw_simple_beam(self.simple_beam_power_canvas, 50, 80)
            self.draw_power(self.simple_beam_power_canvas, 50 + 200 * a / L,
                            80, self.simple_beam_power_F_entry.get())
        except:
            self.warning()

    # 布局均布载荷简支梁界面
    def simple_beam_UL_interface(self):
        # 清空界面
        self.initial_text.pack_forget()
        for i in self.cantilever_beam_moment_list:
            i.grid_forget()
        for i in self.cantilever_beam_power_list:
            i.grid_forget()
        for i in self.cantilever_beam_UL_list:
            i.grid_forget()
        for i in self.simple_beam_moment_list:
            i.grid_forget()
        for i in self.simple_beam_power_list:
            i.grid_forget()
        # 布局组件
        self.simple_beam_UL_q_label.grid(row=0, column=0, sticky='E')
        self.simple_beam_UL_q_entry.grid(row=0, column=1, sticky='E')
        self.simple_beam_UL_q_val.set("1")
        self.simple_beam_UL_E_label.grid(row=1, column=0, sticky='E')
        self.simple_beam_UL_E_entry.grid(row=1, column=1, sticky='E')
        self.simple_beam_UL_E_val.set("1")
        self.simple_beam_UL_I_label.grid(row=2, column=0, sticky='E')
        self.simple_beam_UL_I_entry.grid(row=2, column=1, sticky='E')
        self.simple_beam_UL_I_val.set("1")
        self.simple_beam_UL_l_label.grid(row=3, column=0, sticky='E')
        self.simple_beam_UL_l_entry.grid(row=3, column=1, sticky='E')
        self.simple_beam_UL_l_val.set("1")
        self.simple_beam_UL_button.grid(row=4, column=0, columnspan=2)
        self.simple_beam_UL_w_label.grid(row=5, column=0, sticky='E')
        self.simple_beam_UL_w_entry.grid(row=5, column=1, sticky='E')
        self.simple_beam_UL_w_val.set("")
        self.simple_beam_UL_angleA_label.grid(row=6, column=0, sticky='E')
        self.simple_beam_UL_angleA_entry.grid(row=6, column=1, sticky='E')
        self.simple_beam_UL_angleA_val.set("")
        self.simple_beam_UL_angleB_label.grid(row=7, column=0, sticky='E')
        self.simple_beam_UL_angleB_entry.grid(row=7, column=1, sticky='E')
        self.simple_beam_UL_angleB_val.set("")
        self.simple_beam_UL_canvas.grid(row=0, column=2, rowspan=7)
        self.simple_beam_UL_canvas.delete("all")
        self.simple_beam_UL_canvas.create_text(150,
                                               160,
                                               text="示意图",
                                               anchor='s')

    # 显示均布载荷计算结果
    def simple_beam_UL_determine(self):
        try:
            # 清除输出口
            self.simple_beam_UL_canvas.delete("all")
            self.simple_beam_UL_canvas.create_text(150,
                                                   160,
                                                   text="示意图",
                                                   anchor='s')
            # 计算参数
            L = float(self.simple_beam_UL_l_entry.get())
            coefficient_w = -float(self.simple_beam_UL_q_entry.get()) / (
                24 * float(self.simple_beam_UL_E_entry.get()) * 10**9 *
                float(self.simple_beam_UL_I_entry.get()) / 10**8)
            angle_A = coefficient_w * L**3
            angle_B = -angle_A
            # 显示结果
            self.simple_beam_UL_angleA_val.set("%0.7f " % angle_A)
            self.simple_beam_UL_angleB_val.set("%0.7f " % angle_B)
            self.simple_beam_UL_w_val.set("w=%0.7f*x*(%0.2f-%0.2f*x^2+x^3)" %
                                          (coefficient_w, L**3, 2 * L))
            # 绘制示意图
            self.draw_simple_beam(self.simple_beam_UL_canvas, 50, 80)
            self.draw_UL(self.simple_beam_UL_canvas, 50, 80,
                         self.simple_beam_UL_q_entry.get())
        except:
            self.warning()

    # 创建教程窗口
    def course(self):
        self.help_top = tkinter.Toplevel()
        self.help_top.title("教程")
        self.help_label = tkinter.Label(
            self.help_top,
            justify="left",
            text="使用步骤如下：\n1.从菜单栏中选择梁的种类和受力类型；\n2.输入受\
力值、弹性模量、惯性矩等参数；\n3.点击确定按钮，从下面文本框可以读取挠度方程和端截\
面转角，从右侧可以看到受力示意图。\n\n注：\n1.此处仅可以计算悬臂梁和简支梁模型，外\
伸梁可以基于这两种情况用叠加法计算；\n2.由于此处解算进行了对称弯曲假设和纯弯曲假设\
，计算结果仅适用于横截面关于剪力方向对称的细长梁；\n3.此处仅计算受力点在自由端或全\
梁受均布载荷等最基本情况，其他情况可以根据端截面转角或叠加法方便地算出。")
        self.help_label.pack()

    # 创建关于窗口
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
    d = deflectionEquationSolution()
