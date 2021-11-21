import cv2
import pyrealsense2 as rs
import numpy as np
import time


if __name__ == '__main__':
    start = time.time()
    pipeline = rs.pipeline()
    pipeline.start()

    frames = pipeline.wait_for_frames()
    color_rs = frames.get_color_frame()
    color = np.asanyarray(color_rs.get_data())

    result = cv2.VideoWriter("video.mp4", cv2.VideoWriter_fourcc(*'MP4V'), 20.0, (640, 480))

    temporal_filter = rs.temporal_filter()

    while time.time() - start < 5:
        frames = pipeline.wait_for_frames()
        color_rs = frames.get_color_frame()
        color = np.asanyarray(color_rs.get_data())

        result.write(color)

    result.release()