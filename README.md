# GraphicsLibrary

## 项目概述
这是一个简单的图形函数库，使用 Windows API 实现绘制直线段、圆弧、椭圆弧、填充多边形区域以及显示名字等功能。该项目采用 C++ 编写，并使用 CMake 构建工具。

## 功能列表
- 绘制直线段
- 绘制圆弧
- 绘制椭圆弧
- 多边形区域填充
- 显示名字

## 编译与运行

1. 安装 [CMake](https://cmake.org/download/) 和 [Visual Studio](https://visualstudio.microsoft.com/)，并确保在 Windows 上能够构建 C++ 程序。

2. 使用以下命令编译并运行项目：

```bash
mkdir build
cd build
cmake ..
cmake --build .
.\GraphicsLibrary.exe
```