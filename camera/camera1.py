import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # brown range
    lower_brown = np.array([5, 80, 40])
    upper_brown = np.array([25, 255, 200])

    # black range
    lower_black = np.array([0, 0, 0])
    upper_black = np.array([180, 255, 50])

    brown_mask = cv2.inRange(hsv, lower_brown, upper_brown)
    black_mask = cv2.inRange(hsv, lower_black, upper_black)

    brown_pixels = cv2.countNonZero(brown_mask)
    black_pixels = cv2.countNonZero(black_mask)

    label = "BROWN" if brown_pixels > black_pixels else "BLACK"

    cv2.putText(frame, f"Detected: {label}", (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Live", frame)
    cv2.imshow("Brown Mask", brown_mask)
    cv2.imshow("Black Mask", black_mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
