import cv2
import numpy as np

cap = cv2.VideoCapture(0)

count = 0
while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    lower_brown = np.array([5, 80, 40])
    upper_brown = np.array([25, 255, 200])

    brown_mask = cv2.inRange(hsv, lower_brown, upper_brown)
    brown_pixels = cv2.countNonZero(brown_mask)

    if brown_pixels > 500:   # threshold (tune this)
        print("BROWN + detected! Count:", count)
        count += 1

    cv2.imshow("Live", frame)
    cv2.imshow("Brown Mask", brown_mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()