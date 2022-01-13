# -*-coding:utf-8-*-
# 模块化编程

# 编程语言中的模块化构造
# 汇编语言：子例程,宏
# 高级语言：函数,过程,有的语言不加区分,统称为函数
# 包，模块，函数库，类库


# 编程实例：画一棵树
print("   *")
print("  ***")
print(" *****")
print("*******")
print("   *")
print("  ***")
print(" *****")
print("*******")
print("   #")
print("   #")
print("   #")


# 函数用途：减少重复代码
def treetop():
    print("   *")
    print("  ***")
    print(" *****")
    print("*******")


def tree():
    treetop()
    treetop()
    print("   #")
    print("   #")
    print("   #")


tree()


# 函数用途：改善程序结构
def treetop1():
    treetop()
    treetop()


def treetrunk():
    print("   #")
    print("   #")
    print("   #")


def main():
    treetop1()
    treetrunk()


main()


# 函数用途:提高程序通用性
def treetop2(ch):
    print("   %s" % (ch))
    print("  %s" % (3*ch))
    print(" %s" % (5*ch))
    print("%s" % (7*ch))


def treetop3():
    treetop2('*')
    treetop2('*')


def main1():
    treetop3()
    treetrunk()


main1()
