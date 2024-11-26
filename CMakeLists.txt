cmake_minimum_required(VERSION 3.10)
project(GraphicsLibrary)

set(CMAKE_CXX_STANDARD 11)

# 指定 Windows SDK 目录
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DUNICODE /D_UNICODE")

add_executable(GraphicsLibrary src/main.cpp src/graphics.cpp)
