import cv2
import numpy as np

cap = cv2.VideoCapture(0)

count = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # dark brown range (lower V)
    lower_dark_brown = np.array([5, 80, 20])
    upper_dark_brown = np.array([25, 255, 100])

    mask = cv2.inRange(hsv, lower_dark_brown, upper_dark_brown)
    pixels = cv2.countNonZero(mask)

    if pixels > 500:   # tune threshold
        print("DARK BROWN detected! Count:", count)
        count += 1

    cv2.imshow("Live", frame)
    cv2.imshow("Dark Brown Mask", mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()