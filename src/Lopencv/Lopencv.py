import cv2
import numpy as np

img = cv2.imread("D:/Pictures/texture/xx.png", cv2.IMREAD_GRAYSCALE)
edges = cv2.Canny(img, 50, 200, 3)
contours, hierarchy = cv2.findContours(
    edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
)
for i in range(len(contours)):
    rect = cv2.minAreaRect(contours[i])
    box = cv2.boxPoints(rect)
    box = np.int0(box)
    cv2.drawContours(img, [box], 0, (0, 0, 255), 2)

cv2.imshow("Result", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
