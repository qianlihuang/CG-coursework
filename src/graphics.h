#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
void DrawArc(HDC hdc, int cx, int cy, int radius, int startAngle, int endAngle, COLORREF color);
void DrawEllipseArc(HDC hdc, int cx, int cy, int a, int b, int startAngle, int endAngle, COLORREF color);
void FillPolygon(HDC hdc, POINT *points, int n, COLORREF color);
void DrawName(HDC hdc, const char *name, int x, int y, COLORREF color);

#endif // GRAPHICS_H
