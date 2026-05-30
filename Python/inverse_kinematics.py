import numpy as np

def map_hand_to_arm(points):

    wrist = points[0]
    thumb = points[4]
    index_tip = points[8]

    base = int(wrist[0] * 180)

    shoulder = int(
        np.interp(
            wrist[1],
            [0,1],
            [180,0]
        )
    )

    elbow = int(
        np.interp(
            index_tip[1],
            [0,1],
            [180,0]
        )
    )

    wrist_pitch = int(
        np.interp(
            thumb[1],
            [0,1],
            [180,0]
        )
    )

    wrist_rotate = int(
        np.interp(
            thumb[0],
            [0,1],
            [0,180]
        )
    )

    pinch_distance = abs(
        thumb[0] - index_tip[0]
    )

    gripper = int(
        np.interp(
            pinch_distance,
            [0.02,0.20],
            [0,90]
        )
    )

    return (
        base,
        shoulder,
        elbow,
        wrist_pitch,
        wrist_rotate,
        gripper
    )