import cv2
cap=cv2.VideoCapture(0)

while True:
    ret,frame=cap.read()
    if not ret: break

    x,y,w,h=100,100,300,250
    roi=frame[y:y+h,x:x+w]

    cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
    cv2.imshow("Full Frame",frame)
    cv2.imshow("Soil ROI",roi)

    if cv2.waitKey(1)&0xFF==ord('q'): break

cap.release()
cv2.destroyAllWindows()