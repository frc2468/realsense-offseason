#include <iostream>
#include <librealsense2/rs.hpp>


int main(int argc, char * argv[])try {
    rs2::pipeline pipe;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_POSE);
    pipe.start(cfg);

    while(true) {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::frame frame = frames.first_or_default(RS2_STREAM_POSE);
        rs2_pose pose_sample = frame.as<rs2::pose_frame>().get_pose_data();
        std::cout << "position (" << pose_sample.translation.x << ", " << pose_sample.translation.y << ", " << pose_sample.translation.z << std::endl;
    }

    return 0;
} catch (const rs2::error & e) {
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return -1;
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
}
