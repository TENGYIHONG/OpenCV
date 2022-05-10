# CMakeList.txt: 9.cmake_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("9.cmake_test")

# 将源代码添加到此项目的可执行文件。
add_executable (9.cmake_test "9.cmake_test.cpp" "9.cmake_test.h")

# TODO: 如有需要，请添加测试并安装目标。
#FIND_PACKAGE（OpenCV 4.5.5 REQUIRED core）
