#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

// 绘制直线
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);

// 绘制圆弧
void DrawArc(HDC hdc, int cx, int cy, int radius, int startAngle, int endAngle, COLORREF color);

// 绘制椭圆弧
void DrawEllipseArc(HDC hdc, int cx, int cy, int a, int b, int startAngle, int endAngle, COLORREF color);

// 填充多边形
void FillPolygon(HDC hdc, POINT *points, int n, COLORREF color);

// 绘制名字
void DrawName(HDC hdc, const wchar_t *name, int x, int y, COLORREF color);

#endif // GRAPHICS_H
