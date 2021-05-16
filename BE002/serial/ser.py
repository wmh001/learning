import serial

ser = serial.Serial("COM20")

while True:
    a = input("please,q for quit")
    print(a)
    if a == 'q':
        break
    ser.write(a.encode())
