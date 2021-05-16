# -*-coding:utf-8-*-

import tkinter
root = tkinter.Tk()
root.title("My GUI")
root.geometry("400x400")
aLabel = tkinter.Label(root, text="Hello World")
aLabel.pack()
aButton = tkinter.Button(root, text="Ok", fg="red", bg="green", command=root.quit)
aButton.pack()


def f():
    print("Hello!")


bButton = tkinter.Button(root, text="Print", fg="blue", command=f)
bButton.pack()

tkinter.Checkbutton(root, text="Math").pack()
tkinter.Checkbutton(root, text="Python").pack()
tkinter.Checkbutton(root, text="English").pack()
v1 = tkinter.IntVar()
tkinter.Checkbutton(root, text="Check", variable=v1).pack()

v2 = tkinter.IntVar()
tkinter.Radiobutton(root, text="One", variable=v2, value=1).pack()
tkinter.Radiobutton(root, text="Two", variable=v2, value=2).pack()
tkinter.Radiobutton(root, text="Three", variable=v2, value=3).pack()

v3 = tkinter.StringVar()
e = tkinter.Entry(root, textvariable=v3)
e.pack()

v4 = tkinter.IntVar()
v5 = tkinter.IntVar()
v6 = tkinter.IntVar()
f = tkinter.Frame(root, bd=4, relief="groove")
f.pack()
tkinter.Checkbutton(f, text="Math", variable=v4).pack()
tkinter.Checkbutton(f, text="Python", variable=v5).pack()
tkinter.Checkbutton(f, text="English", variable=v6).pack()

m = tkinter.Menu(root)
root.config(menu=m)


def callback():
    print("hello from menu")


filemenu = tkinter.Menu(m)
m.add_cascade(label="File", menu=filemenu)
filemenu.add_command(label="New", command=callback)
filemenu.add_command(label="Open...", command=callback)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=callback)
helpmenu = tkinter.Menu(m)
m.add_cascade(label="Help", menu=helpmenu)
helpmenu.add_command(label="About...", command=callback)

tkinter.Label(root, text="hello").pack()
top = tkinter.Toplevel()
tkinter.Label(top, text="world").pack()
top.title('hello toplevel')
top.geometry('400x300')

root2 = tkinter.Tk()
tkinter.Label(root2, text="ID Number:").grid()
tkinter.Label(root2, text="Name:").grid()
tkinter.Entry(root2).grid(row=0, column=1)
tkinter.Entry(root2).grid(row=1, column=1)

root3 = tkinter.Tk()
tkinter.Label(root3, text="ID Number:").grid(sticky="E")
tkinter.Label(root3, text="Name:").grid(sticky="E")
tkinter.Entry(root3).grid(row=0, column=1)
tkinter.Entry(root3).grid(row=1, column=1)
tkinter.Checkbutton(root3, text="Registered User").grid(columnspan=2, sticky="W")
tkinter.Label(root3, text="X").grid(row=0, column=2, columnspan=2, rowspan=2, sticky="W"+"E"+"N"+"S")
tkinter.Button(root3, text="Zoom In").grid(row=2, column=2)
tkinter.Button(root3, text="Zoom Out").grid(row=2, column=3)

root.mainloop()
root2.mainloop()
root3.mainloop()
print(v1.get())
print(v2.get())
print(v3.get())
