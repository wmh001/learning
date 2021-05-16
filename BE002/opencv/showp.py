import cv2

img = cv2.imread("15863462789642.jpg")
cap = cv2.VideoCapture(0)

while True:
    ret, img = cap.read()

    img[0:100, 0:100] = img[300:400, 300:400]

    for i in range(3):
        for j in range(3):
            img[i * 100:i * 100 + 100, j * 110:j * 110 + 100] = img[300:400,
                                                                    300:400]
    for i in range(3):
        for j in range(3):
            cv2.rectangle(img, (i * 110, j * 100),
                          (i * 110 + 100, j * 100 + 100), (0, 255, 0), 3)
    cv2.imshow("hh", img)
    cv2.waitKey(100)


cap.release()
cv2.destryAllWindows()
