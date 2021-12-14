cmake_minimum_required(VERSION 3.1.0)
project(rpi2468)

include(FetchContent)


find_package(realsense2)
if (NOT realsense2_FOUND)
    FetchContent_Declare(realsense2
        GIT_REPOSITORY "https://github.com/IntelRealSense/librealsense.git"
        GIT_TAG "2.50.0"
        )
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${realsense2_LIBRARY})
