#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>

#include <librealsense2/rs.hpp>

#include "pose_handler.hpp"

const std::vector<rs2_stream> streams = {
RS2_STREAM_POSE
};

using namespace frc2468;

int main(int argc, char * argv[]) try {
    std::queue<rs2::pose_frame> pose_queue;


    rs2::context ctx;

    for (const rs2::device&& dev : ctx.query_devices()) {
        std::cout << dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) << std::endl;
    }


    rs2::pipeline pipe;
    rs2::config cfg;
    for (const rs2_stream& stream : streams) {
        cfg.enable_stream(stream);
    }



    std::mutex data_mutex;
    auto callback = [&](const rs2::frame& frame) {
        std::lock_guard<std::mutex> lock(data_mutex);

        if (auto fp = frame.as<rs2::pose_frame>()) {
            pose_queue.push(fp);
            handle_pose_frame(pose_queue);
        }
    };

    pipe.start(cfg, callback);



    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
} catch (const rs2::error & e) {
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return -1;
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
}
