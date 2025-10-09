/**
 * 这个文件是工具库的源文件
 * 想要实现的和游戏无关的函数，都可以扔在这里
 */

#include "stdafx.h"

#include "config.h"

#include "util.h"

// 向量模长
double Length(Vector2 in)
{
    return sqrt(in.x * in.x + in.y * in.y);
}

// 归一化向量
Vector2 Normalize(Vector2 in)
{
    double length = Length(in);
    if (length == 0)
    {
        return {0, 0};
    }
    Vector2 out = {in.x / length, in.y / length};
    return out;
}

// 创建纯色图像
HBITMAP CreateBackground(HWND hWnd, COLORREF color)
{
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, bmp_output);

    // 创建纯白色画刷
    HBRUSH hBrush = CreateSolidBrush(color);

    // 创建一个矩形
    RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    // 将缓存填充为白色
    FillRect(hdc_memBuffer, &rect, hBrush);

    // 回收资源所占的内存（非常重要）
    DeleteObject(hBrush);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);

    return bmp_output;
}
