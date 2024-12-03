#include <windows.h>
#include "graphics.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // 绘制红色的直线
            DrawLine(hdc, 50, 50, 400, 50, RGB(255, 0, 0));
            
            // 绘制绿色的半圆弧
            DrawArc(hdc, 300, 200, 100, 0, 180, RGB(0, 255, 0));
            
            // 绘制蓝色的椭圆弧
            DrawEllipseArc(hdc, 500, 200, 100, 60, 0, 180, RGB(0, 0, 255));
            
            // 绘制黄色的三角形
            POINT points[] = {{150, 150}, {250, 150}, {200, 250}};
            FillPolygon(hdc, points, 3, RGB(255, 255, 0));
            
            // 绘制紫色的名字
            DrawName(hdc, L"YILIU DONG", 150, 350, RGB(255, 0, 255));

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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"GraphicsWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Graphics Library", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                               NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
