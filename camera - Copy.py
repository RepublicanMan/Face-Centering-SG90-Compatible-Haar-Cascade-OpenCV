from ultralytics import YOLO
import cv2

model = YOLO("C:\\Users\\traps\\OneDrive\\Documents\\SCHOOL\\ABINUS BINUS BINUS\\Semester 5\\Body Tracking Robotic Arm\\best.pt")

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    results = model(frame, conf=0.4)
    annotated = results[0].plot()

    cv2.imshow("YOLOv8 Camera", annotated)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
