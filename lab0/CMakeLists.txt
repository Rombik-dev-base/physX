cmake_minimum_required(VERSION 3.15)
project(Figures)

set(CMAKE_CXX_STANDARD 14)

add_executable(Figures main.cpp)
target_link_libraries(Figures -lOpenGL32 -lfreeGLUT)