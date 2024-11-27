#include "graphics.h"
#include <cmath>
#include <vector>
#include <algorithm>

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

void DrawName(HDC hdc, const wchar_t *name, int x, int y, COLORREF color) {
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT); // 透明背景
    TextOutW(hdc, x, y, name, wcslen(name));
}
