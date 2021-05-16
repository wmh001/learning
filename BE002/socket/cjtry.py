import socket

s = socket.socket()
s.connect(("127.0.0.1", 25566))

print("conneted")

while True:
    msg = input("$")
    if "\\" in msg:
        break
    s.send(msg.encode("ascii"))
s.close()
