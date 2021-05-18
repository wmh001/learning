# -*-coding:utf-8-*-

# 综合利用原型法、面向对象编程、GUI编程等方法设计一个汽车类Car，以模拟汽车功能。
# 作为一个汽车对象，拥有的数据包括型号，当前状态(On/Off) ，当前速度，当前油量等；
# 能够执行的方法包括开关（使汽车切换On/Off状态），踩油门或刹车（加速/减速）以及导航屏幕，音乐播放等等。
# 从最简单的设计开始，在课堂时间内尽量完善功能。

import tkinter
from tkinter.constants import ALL
import winsound


class Car:
    def __init__(self, model):
        self.model = model
        self.state = 'Off'
        self.speed = 0
        self.oil = 70

        self.root = tkinter.Tk()
        self.root.title('Mycar')

        self.model_label = tkinter.Label(self.root,
                                         text="车型:" + model,
                                         bg='white')
        self.model_label.grid(row=0, column=0, columnspan=7, sticky='nsew')

        self.status_label = tkinter.Label(self.root,
                                          text="当前状态为" + self.state,
                                          fg='red',
                                          bg='black')
        self.status_label.grid(row=1, column=0, sticky='nsew')
        self.status_button = tkinter.Button(self.root,
                                            text='开关',
                                            command=self.switch)
        self.status_button.grid(row=1, column=1, columnspan=2, sticky='nsew')

        self.speed_label = tkinter.Label(self.root,
                                         text="当前速度为" + str(self.speed),
                                         fg='red',
                                         bg='black')
        self.speed_label.grid(row=2, column=0, sticky='nsew')
        self.speed_up_button = tkinter.Button(self.root,
                                              text='加速',
                                              command=self.speed_up)
        self.speed_up_button.grid(row=2, column=1, sticky='nsew')
        self.speed_down_button = tkinter.Button(self.root,
                                                text='减速',
                                                command=self.speed_down)
        self.speed_down_button.grid(row=2, column=2, sticky='nsew')

        self.oil_label = tkinter.Label(self.root,
                                       text="当前油量为" + str(self.oil),
                                       fg='red',
                                       bg='black')
        self.oil_label.grid(row=3, column=0, sticky='nsew')
        self.oil_button = tkinter.Button(self.root, text='加油', command=self.fill_up)
        self.oil_button.grid(row=3, column=1, columnspan=2, sticky='nsew')

        self.navigation = tkinter.Canvas(self.root,
                                         width=200,
                                         height=95,
                                         bg='white')
        self.navigation.create_oval(198, 88, 202, 92, fill='red', outline='')
        self.navigation.grid(row=1, column=4, rowspan=3, columnspan=3)
        self.navigation.bind('<Button-1>', self.show_route)
        self.navigation_button = tkinter.Button(self.root,
                                                text='清除已有路线',
                                                command=self.clean_route)
        self.navigation_button.grid(row=4,
                                    column=4,
                                    columnspan=3,
                                    sticky='nsew')

        self.music_button = tkinter.Button(self.root,
                                           text='播放音乐',
                                           command=self.play_music)
        self.music_button.grid(row=4, column=0, columnspan=3, sticky='nsew')

        self.root.mainloop()

    def switch(self):
        if self.state == 'Off':
            self.state = 'On'
        else:
            self.state = 'Off'
            self.speed = 0
            self.speed_label['text'] = "当前速度为0"
        self.status_label['text'] = "当前状态为" + self.state

    def speed_up(self):
        if self.state == 'On':
            if self.oil > 0:
                self.speed = self.speed + 10
                self.oil = self.oil - 1
                self.oil_label['text'] = "当前油量为" + str(self.oil)
            else:
                self.speed = 0
        self.speed_label['text'] = "当前速度为" + str(self.speed)

    def speed_down(self):
        if self.state == 'On' and self.oil > 0:
            if self.speed > 10:
                self.speed = self.speed - 10
                self.oil = self.oil - 1
                self.oil_label['text'] = "当前油量为" + str(self.oil)
            elif self.speed > 0:
                self.speed = 0
                self.oil = self.oil - 1
                self.oil_label['text'] = "当前油量为" + str(self.oil)

        elif self.state == 'On':
            self.speed = 0
        self.speed_label['text'] = "当前速度为" + str(self.speed)

    def fill_up(self):
        self.oil = 70
        self.oil_label['text'] = "当前油量为" + str(self.oil)

    def show_route(self, event):
        x, y = event.x, event.y
        self.navigation.create_line(x, y, x, 90, arrow='last')
        self.navigation.create_line(x, 90, 200, 90, arrow='last')

    def clean_route(self):
        self.navigation.delete(ALL)
        self.navigation.create_oval(198, 88, 202, 92, fill='red', outline='')

    def play_music(self):
        for n, d in [(784, 1000), (784, 500), (880, 500), (587, 2000),
                     (523, 1000), (523, 500), (440, 500), (587, 2000)]:
            winsound.Beep(n, d)


Car('Jetta')
