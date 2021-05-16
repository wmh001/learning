sum = 0
# 取1到1000中3的倍数依次循环
for i in range(0, 1001, 3):
    # 是否能被不能被5整除
    if (i % 5 != 0):
        # 求和
        sum += i
# 输出
print(sum)
