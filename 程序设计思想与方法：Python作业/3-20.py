sum = 0
for i in range(1, 1001):
    if (i % 3 == 0) and (i % 5 != 0):
        sum += i
print(sum)
