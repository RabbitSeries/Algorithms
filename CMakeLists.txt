cmake_minimum_required(VERSION 3.10.0)
project(Algorithms VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(Algorithms "LibGrammar/OpenCVEnv/main.cpp" "LibGrammar/OpenCVEnv/solution.cpp")
target_link_libraries(Algorithms ${OpenCV_LIBS})

set(workingPath "${CMAKE_SOURCE_DIR}")
