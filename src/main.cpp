#include <windows.h>
#include "graphics.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // 绘制图形
            DrawLine(hdc, 50, 50, 400, 50, RGB(255, 0, 0));  // 红色直线
            DrawArc(hdc, 250, 250, 100, 0, 180, RGB(0, 255, 0));  // 绿色半圆
            DrawEllipseArc(hdc, 250, 250, 100, 60, 0, 180, RGB(0, 0, 255));  // 蓝色椭圆弧
            POINT points[] = {{100, 100}, {200, 100}, {150, 200}};
            FillPolygon(hdc, points, 3, RGB(255, 255, 0));  // 黄色填充三角形
            
            // 显示名字
            DrawName(hdc, "Yiliu Dong", 150, 300, RGB(255, 0, 255));  // 紫色名字
            
            EndPaint(hwnd, &ps);
        } break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    const char CLASS_NAME[] = "GraphicsWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Graphics Library", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                               NULL, NULL, wc.hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
