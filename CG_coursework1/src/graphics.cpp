#include "graphics.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <wchar.h>

// 绘制直线的函数
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        SetPixel(hdc, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

// 绘制圆弧的函数
void DrawArc(HDC hdc, int cx, int cy, int radius, int startAngle, int endAngle, COLORREF color) {
    float startRad = startAngle * 3.14159f / 180;
    float endRad = endAngle * 3.14159f / 180;
    float step = 1.0f / radius; // 根据半径动态调整步长

    for (float angle = startRad; angle <= endRad; angle += step) {
        int x = cx + static_cast<int>(radius * cos(angle));
        int y = cy + static_cast<int>(radius * sin(angle));
        SetPixel(hdc, x, y, color);
    }
}

// 绘制椭圆弧的函数
void DrawEllipseArc(HDC hdc, int cx, int cy, int a, int b, int startAngle, int endAngle, COLORREF color) {
    float startRad = startAngle * 3.14159f / 180;
    float endRad = endAngle * 3.14159f / 180;
    float step = 1.0f / std::max(a, b);

    for (float angle = startRad; angle <= endRad; angle += step) {
        int x = cx + static_cast<int>(a * cos(angle));
        int y = cy + static_cast<int>(b * sin(angle));
        SetPixel(hdc, x, y, color);
    }
}

// 填充多边形的函数
void FillPolygon(HDC hdc, POINT *points, int n, COLORREF color) {
    LONG yMin = points[0].y, yMax = points[0].y;
    for (int i = 1; i < n; i++) {
        yMin = std::min(yMin, points[i].y);
        yMax = std::max(yMax, points[i].y);
    }

    for (LONG y = yMin; y <= yMax; y++) {
        std::vector<int> intersections;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if ((points[i].y <= y && points[j].y > y) || (points[i].y > y && points[j].y <= y)) {
                int x = points[i].x + (y - points[i].y) * (points[j].x - points[i].x) / (points[j].y - points[i].y);
                intersections.push_back(x);
            }
        }

        std::sort(intersections.begin(), intersections.end());
        for (size_t i = 0; i + 1 < intersections.size(); i += 2) { // 防止越界
            for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                SetPixel(hdc, x, y, color);
            }
        }
    }
}

// 绘制单个字母 'Y' 的函数
void DrawLetterY(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x, y, x + 10, y + 20, color);    // 左上到中间
    DrawLine(hdc, x + 20, y, x + 10, y + 20, color); // 右上到中间
    DrawLine(hdc, x + 10, y + 20, x + 10, y + 40, color);  // 中间到下
}

// 绘制字母 'I' 的函数
void DrawLetterI(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x + 10, y, x + 10, y + 40, color);  // 垂直线
    DrawLine(hdc, x, y, x + 20, y, color);            // 顶部横线
    DrawLine(hdc, x, y + 40, x + 20, y + 40, color);  // 底部横线
}

// 绘制字母 'L' 的函数
void DrawLetterL(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x, y, x, y + 40, color);           // 垂直线
    DrawLine(hdc, x, y + 40, x + 20, y + 40, color); // 底部横线
}

// 绘制字母 'U' 的函数
void DrawLetterU(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x, y, x, y + 40, color);           // 左垂直线
    DrawLine(hdc, x + 20, y, x + 20, y + 40, color); // 右垂直线
    DrawLine(hdc, x, y + 40, x + 20, y + 40, color); // 底部横线
}

// 绘制字母 'D' 的函数
void DrawLetterD(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x, y, x, y + 40, color);           // 垂直线
    DrawArc(hdc, x, y + 20, 20, 270, 450, color); // 半圆弧（右边）
}

// 绘制字母 'O' 的函数
void DrawLetterO(HDC hdc, int x, int y, COLORREF color) {
    DrawArc(hdc, x + 20, y + 20, 20, 0, 360, color); // 完整圆形
}

// 绘制字母 'N' 的函数
void DrawLetterN(HDC hdc, int x, int y, COLORREF color) {
    DrawLine(hdc, x, y, x, y + 40, color);          // 左垂直线
    DrawLine(hdc, x + 20, y, x + 20, y + 40, color); // 右垂直线
    DrawLine(hdc, x, y, x + 20, y + 40, color);      // 斜线
}

// 绘制字母 'G' 的函数
void DrawLetterG(HDC hdc, int x, int y, COLORREF color) {
    DrawArc(hdc, x + 20, y + 20, 20, 0, 270, color); // 弧形（3/4圆）
    DrawLine(hdc, x + 20, y + 20, x + 40, y + 20, color); // 底部横线
}

// 绘制名字的函数
void DrawName(HDC hdc, const wchar_t *name, int x, int y, COLORREF color) {
    for (int i = 0; i < wcslen(name); ++i) {
        wchar_t letter = name[i];
        switch (letter) {
            case L'Y': DrawLetterY(hdc, x, y, color); break;
            case L'I': DrawLetterI(hdc, x, y, color); break;
            case L'L': DrawLetterL(hdc, x, y, color); break;
            case L'U': DrawLetterU(hdc, x, y, color); break;
            case L'D': DrawLetterD(hdc, x, y, color); break;
            case L'O': DrawLetterO(hdc, x, y, color); break;
            case L'N': DrawLetterN(hdc, x, y, color); break;
            case L'G': DrawLetterG(hdc, x, y, color); break;
            default: 
                // 如果字母不在case中，直接绘制字母
                SetTextColor(hdc, color);
                SetBkMode(hdc, TRANSPARENT); // 透明背景
                TextOutW(hdc, x, y, &letter, 1); 
                break;
        }
        x += 38; // 设置字母之间的间距
    }
}
