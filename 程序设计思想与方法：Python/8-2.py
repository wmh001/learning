# -*-coding:utf-8-*-

import tkinter


class MyApp:
    def __init__(self):
        self.root = tkinter.Tk()
        self.t = tkinter.Label(self.root, text="Spam")
        self.t.pack()
        tkinter.Button(self.root, text="Play", command=self.changeText).pack()
        tkinter.Button(self.root, text="Quit", command=self.root.quit).pack()
        self.root.mainloop()
        self.root.destroy()

    def changeText(self):
        if self.t["text"] == "Spam":
            self.t["text"] = "Egg"
        else:
            self.t["text"] = "Spam"


app = MyApp()
