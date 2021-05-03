# coding:utf-8

# 交通工具类
class Vehicle:
    def __init__(self, s):
        # 速度
        self.speed = s

    def getSpeed(self):
        return self.speed

    def setSpeed(self, s):
        self.speed = s

    # 加速
    def speedUp(self, addSpeed):
        self.speed = self.speed + addSpeed

    # 减速
    def speedDown(self, subSpeed):
        self.speed = self.speed - subSpeed


# 汽车类
class Car(Vehicle):
    def __init__(self, s, b):
        Vehicle.__init__(self, s)
        # 品牌
        self.brand = b

    def getBrand(self):
        return self.brand

    def setBrand(self, b):
        self.brand = b


# 飞机类
class Airplane(Vehicle):
    def __init__(self, s, h):
        Vehicle.__init__(self, s)
        # 高度
        self.height = h

    def getHeight(self):
        return self.height

    def setHeight(self, h):
        self.height = h

    # 上升
    def ascend(self, addHeight):
        self.height = self.height + addHeight

    # 下降
    def descend(self, subSpeed):
        self.height = self.height - subSpeed


def main():
    c = Car(60, "大众")
    print("现在的速度是" + str(c.getSpeed()) + "km/h")
    print("品牌是" + c.getBrand())
    c.setSpeed(70)
    print("现在的速度是" + str(c.getSpeed()) + "km/h")
    c.speedUp(10)
    print("现在的速度是" + str(c.getSpeed()) + "km/h")
    c.speedDown(10)
    print("现在的速度是" + str(c.getSpeed()) + "km/h")

    a = Airplane(800, 9000)
    print("现在的速度是" + str(a.getSpeed()) + "km/h")
    print("现在的高度是" + str(a.getHeight()) + "m")
    a.setSpeed(900)
    print("现在的速度是" + str(a.getSpeed()) + "km/h")
    a.speedUp(50)
    print("现在的速度是" + str(a.getSpeed()) + "km/h")
    a.speedDown(50)
    print("现在的速度是" + str(a.getSpeed()) + "km/h")
    a.ascend(100)
    print("现在的高度是" + str(a.getHeight()) + "m")
    a.descend(100)
    print("现在的高度是" + str(a.getHeight()) + "m")


main()
