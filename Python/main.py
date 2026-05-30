import cv2

from hand_tracking import HandTracker
from serial_controller import RobotArm
from inverse_kinematics import map_hand_to_arm

tracker = HandTracker()
robot = RobotArm('COM3')

cap = cv2.VideoCapture(0)

while True:

    success, frame = cap.read()

    landmarks = tracker.get_landmarks(frame)

    if len(landmarks) == 21:

        angles = map_hand_to_arm(
            landmarks
        )

        robot.send_angles(*angles)

        cv2.putText(
            frame,
            str(angles),
            (10,30),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (0,255,0),
            2
        )

    cv2.imshow(
        "Robot Arm Control",
        frame
    )

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()