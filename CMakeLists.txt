cmake_minimum_required(VERSION 3.5.0)
project(Algorithms VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加生成可执行文件的目标
add_executable(Algorithms main.cpp)

# 查找所有 .cpp 和 .h 文件
file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp" "*.h")


# 自定义目标来检查语法
# add_custom_target(
#     check_syntax
#     COMMAND ${CMAKE_CXX_COMPILER} -fsyntax-only $<TARGET_OBJECTS:Algorithms>
#     SOURCES cppversion.cpp
#     COMMENT "Checking syntax for a.cpp and b.cpp"
# )

# 创建一个自定义目标进行语法检查
add_custom_target(
    check_syntax
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++17 -fsyntax-only ${ALL_SOURCE_FILES}
    COMMENT "Checking syntax for all .cpp and .h files"
)

# 使 check_syntax 目标依赖于可执行文件的构建
add_dependencies(check_syntax Algorithms)
