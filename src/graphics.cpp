#include "graphics.h"
#include <cmath>
#include <vector>
#include <algorithm>

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
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
    float startRad = startAngle * 3.14159 / 180;
    float endRad = endAngle * 3.14159 / 180;

    for (float angle = startRad; angle <= endRad; angle += 0.01) {
        int x = cx + radius * cos(angle);
        int y = cy + radius * sin(angle);
        SetPixel(hdc, x, y, color);
    }
}

void DrawEllipseArc(HDC hdc, int cx, int cy, int a, int b, int startAngle, int endAngle, COLORREF color) {
    float startRad = startAngle * 3.14159 / 180;
    float endRad = endAngle * 3.14159 / 180;

    for (float angle = startRad; angle <= endRad; angle += 0.01) {
        int x = cx + a * cos(angle);
        int y = cy + b * sin(angle);
        SetPixel(hdc, x, y, color);
    }
}

void FillPolygon(HDC hdc, POINT *points, int n, COLORREF color) {
    int yMin = points[0].y, yMax = points[0].y;
    for (int i = 1; i < n; i++) {
        if (points[i].y < yMin) yMin = points[i].y;
        if (points[i].y > yMax) yMax = points[i].y;
    }

    for (int y = yMin; y <= yMax; y++) {
        std::vector<int> intersections;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if ((points[i].y <= y && points[j].y > y) || (points[i].y > y && points[j].y <= y)) {
                int x = points[i].x + (y - points[i].y) * (points[j].x - points[i].x) / (points[j].y - points[i].y);
                intersections.push_back(x);
            }
        }

        std::sort(intersections.begin(), intersections.end());
        for (size_t i = 0; i < intersections.size(); i += 2) {
            for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                SetPixel(hdc, x, y, color);
            }
        }
    }
}

void DrawName(HDC hdc, const char *name, int x, int y, COLORREF color) {
    SetTextColor(hdc, color);
    TextOut(hdc, x, y, name, strlen(name));
}
