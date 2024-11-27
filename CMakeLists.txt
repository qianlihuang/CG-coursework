cmake_minimum_required(VERSION 3.10)

# 项目名称
project(GraphicsLibrary)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 设置编译器标志以支持 Unicode
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE -D_UNICODE")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DUNICODE /D_UNICODE")
endif()

# 设置源文件
set(SOURCE_FILES src/main.cpp src/graphics.cpp)

# 创建可执行文件
add_executable(GraphicsLibrary ${SOURCE_FILES})

# 链接 Windows API 库（Gdi32 用于图形）
target_link_libraries(GraphicsLibrary Gdi32)

# 设置目标为 Windows GUI 程序
set_target_properties(GraphicsLibrary PROPERTIES
    WIN32_EXECUTABLE YES  # 这会告诉 CMake 该项目是一个 Windows GUI 程序
)
