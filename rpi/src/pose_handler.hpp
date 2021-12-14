#pragma once

#include <queue>

// For debugging
// TODO: remove this when logging thing is added
#include <iostream>

#include <librealsense2/rs.hpp>

namespace frc2468 {
    void handle_pose_frame(std::queue<rs2::pose_frame>& pose_queue) {
        auto fp = pose_queue.front();

        rs2_pose pose_sample = fp.get_pose_data();
        std::cout << "position (" <<
            pose_sample.translation.x << ", " <<
            pose_sample.translation.y << ", " <<
            pose_sample.translation.z << ")" << std::endl;
    }
}
