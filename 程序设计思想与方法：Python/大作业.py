# -*-coding:utf-8-*-

import tkinter


class deflectionEquationCalculator:
    def __init__(self):
        self.root = tkinter.Tk()
        self.root.title("弯矩方程计算器")

        self.meun = tkinter.Menu(self.root)
        self.root.config(menu=self.meun)
        self.beam_type_meun = tkinter.Menu(self.meun)
        self.meun.add_cascade(label="梁种类", menu=self.beam_type_meun)
        self.beam_type_meun.add_command(label="悬臂梁", command=self.cantilever_beam_label)
        self.beam_type_meun.add_command(label="简支梁", command=self.simply_supported_beam)
        # v.set('new text')
        self.v = tkinter.StringVar()
        self.e = tkinter.Entry(self.root, textvariable=self.v)
        self.e.bind('<Return>', self.stop_input)
        self.root.mainloop()

    def cantilever_beam_label(self):
        self.e.pack()

    def simply_supported_beam(self):
        self.e.pack_forget()

    def stop_input(self, event):
        print(self.v.get())


d = deflectionEquationCalculator()
