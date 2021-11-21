import pyrealsense2 as rs
import cv2
import numpy as np
import time

if __name__ == '__main__':
    # Create a context object. This object owns the handles to all connected realsense devices
    pipeline = rs.pipeline()
    pc = rs.pointcloud()
    pipeline.start()

    temporal_filter = rs.temporal_filter()
    colorizer = rs.colorizer(2)
    align = rs.align(rs.stream.color)

    result = cv2.VideoWriter('video.mp4', cv2.VideoWriter_fourcc(*'MP4V'), 20.0, (640, 480))

    begin = time.time()
    while time.time() - begin < 5:
        start = time.time_ns()
        frames = align.process(pipeline.wait_for_frames())
        color_rs = frames.get_color_frame()
        depth_rs = temporal_filter.process(frames.get_depth_frame())
        color = np.asanyarray(color_rs.get_data())
        depth = np.int16(np.asanyarray(depth_rs.get_data()))
        pc.map_to(color_rs)
        points = pc.calculate(depth_rs)
        v, t = points.get_vertices(), points.get_texture_coordinates()
        vertices = np.asanyarray(v).view(np.float32).reshape(-1, 3)  # xyz
        y_image = (-1 * vertices.reshape((480, 640, 3))[:, :, 1]) + 0.16
        y_image[np.bitwise_or(y_image > 1, depth > 2000)] = 0
        result.write(y_image)
        print((time.time_ns() - start) / 1000000000)

    result.release()
