import pyrealsense2 as rs2

def main():
    pipe = rs2.pipeline()

    pipe.start()
    try:
        while True:
            frames = pipe.wait_for_frames()
            pose = frames.get_pose_frame()
            if pose:
                data = pose.get_pose_data()
                print('Frame num: {}'.format(pose.frame_number))
                print('Position: {}'.format(data.translation))


    finally:
        pipe.stop()



if __name__ == '__main__':
    main()
