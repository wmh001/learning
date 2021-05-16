import cv2

img = cv2.imread("red.jpg")
img[0:100, 0:100] = img[400:500, 400:500]

for i in range(3):
    for j in range(3):
        img[i * 100:i * 100 + 100, j * 100:j * 100 + 100] = img[400:500,
                                                                400:500]
cv2.imshow("fasdlfadsf", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
