/**
 * 这个文件是游戏渲染的源文件
 * 所有视觉的更新，都需要写在这里
 */

#include "stdafx.h"

#include "config.h"

#include "scene.h"
#include "object.h"
#include "ui.h"

extern HBITMAP bmp_WhiteBackground;
extern HBITMAP bmp_BlackBackground;
extern HBITMAP bmp_StartButton;

void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
    HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, blankBmp);

    // 绘制白色背景
    SelectObject(hdc_loadBmp, bmp_WhiteBackground);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 绘制场景物体
    RenderGameObjects(hdc_memBuffer, hdc_loadBmp);

    // 绘制UI
    RenderUi(hdc_memBuffer, hdc_loadBmp);

    // 最后将所有的信息绘制到屏幕上
    BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

    // 回收资源所占的内存（非常重要）
    DeleteObject(blankBmp);
    DeleteDC(hdc_loadBmp);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);
}
