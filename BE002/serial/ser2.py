import serial

ser = serial.Serial("COM21", timeout=1)

while True:
    print("reading...")
    resp = ser.readline()

    # print(resp)
    if resp != b"":
        a = resp.decode()
        print(a)
        print("get commod, I will handle it", resp)
        b = a.strip()
        if b == '~':
            break
        c = b.split(",")
        d = list(map(int, c))
        ser0 = d[0]
        ser1 = d[1]
        ser2 = d[2]
        print("move servo to angle", ser0, ser1, ser2)
    else:
        print("working on something else...")
