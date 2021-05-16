from mcpi.minecraft import Minecraft
import time

mc = Minecraft.create()

pos = mc.player.getTilePos()
print("player pos is", pos)

i = 1
stayed_time = 0
while True:
    print("stay_time" + str(stayed_time))
    time.sleep(1)
    pos = mc.player.getTilePos()
    mc.postToChat("please go to home x=-30 y=20 z=-40 for 15s to fly")
    mc.postToChat("x:" + str(pos.x) + "y:" + str(pos.y) + "z:" + str(pos.z))
    if pos.x == -30 and pos.z == -40 and pos.y == 20:
        mc.postToChat("welcome home")
        stayed_time = stayed_time + 1
        if stayed_time < 10:
            mc.setBlock(pos.x, pos.y - i, pos.z, 1)
            i = i + 1
    else:
        stayed_time = 0
