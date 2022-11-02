cmake_minimum_required(VERSION 3.19)
project(CLionProjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(Qt6_DIR "~/Qt/6.3.1/macos/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(CLionProjects main.cpp SeamCarver.cpp)
target_link_libraries(CLionProjects Qt6::Widgets)
