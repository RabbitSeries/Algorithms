cmake_minimum_required(VERSION 3.10.0)
project(Algorithms VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MAKE_PROGRAM "D:/Build_Tool_Lib/Qt/Tools/Ninja/ninja.exe")
# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/OpenCVEnv)
# include_directories("D:/Qt/6.8.0/mingw_64/include")
# include_directories("D:/Build_Tool_Lib/opencv/opencvMinGW/install/opencv/include")
# link_directories("D:/Build_Tool_Lib/opencv/opencvMinGW/install/opencv/x64/mingw/lib")
# include_directories("/usr/local/include/opencv4")
# link_directories("/usr/local/lib")
include_directories( ${OpenCV_INCLUDE_DIRS} )
# -- Set non-toolchain portion of runtime path of "/usr/local/bin/opencv_annotation" to "/usr/local/lib"
# -- Installing: /usr/local/bin/opencv_visualisation
# -- Set non-toolchain portion of runtime path of "/usr/local/bin/opencv_visualisation" to "/usr/local/lib"
# -- Installing: /usr/local/bin/opencv_interactive-calibration
# -- Set non-toolchain portion of runtime path of "/usr/local/bin/opencv_interactive-calibration" to "/usr/local/lib"
# -- Installing: /usr/local/bin/opencv_version
# -- Set non-toolchain portion of runtime path of "/usr/local/bin/opencv_version" to "/usr/local/lib"
# -- Installing: /usr/local/bin/opencv_model_diagnostics
# -- Set non-toolchain portion of runtime path of "/usr/local/bin/opencv_model_diagnostics" to "/usr/local/lib"


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 添加生成可执行文件的目标
add_executable(Algorithms "LibGrammar/OpenCVEnv/main.cpp" "LibGrammar/OpenCVEnv/solution.cpp")
target_link_libraries( Algorithms ${OpenCV_LIBS} )
# set(CMAKE_MAKE_PROGRAM "D:\\Qt\\Tools\\Ninja\\ninja.exe")
# 查找所有 .cpp 和 .h 文件
# file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp" "*.h")


# 自定义目标来检查语法
# add_custom_target(
#     check_syntax
#     COMMAND ${CMAKE_CXX_COMPILER} -fsyntax-only $<TARGET_OBJECTS:Algorithms>
#     SOURCES cppversion.cpp
#     COMMENT "Checking syntax for a.cpp and b.cpp"
# )

# target_link_libraries(Algorithms libopencv_world4100d libopencv_world4100)
target_link_libraries(Algorithms)



# 假设 workingPath 是 CMake 变量
set(workingPath "${CMAKE_SOURCE_DIR}")
# 定义清理命令
add_custom_target(clean_workspace
    # COMMAND ${CMAKE_COMMAND} -E remove_directory ${workingPath}/bin
    # COMMAND ${CMAKE_COMMAND} -E remove_directory ${workingPath}/build
    COMMAND ${CMAKE_COMMAND} -E remove ${workingPath}/**/*.exe
    COMMAND ${CMAKE_COMMAND} -E remove ${workingPath}/**/*.dll
    COMMAND ${CMAKE_COMMAND} -E remove ${workingPath}/**/*.o
    COMMENT "Cleaning project..."
)
