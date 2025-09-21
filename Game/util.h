/**
 * 这个文件是工具库的头文件
 * 想要实现的和游戏无关的函数，都可以扔在这里
 */

#pragma once

#include "type.h"

// 向量
double Length(Vector2 in);
Vector2 Normalize(Vector2 in);

// 图片
HBITMAP CreateBackground(HWND hWnd, COLORREF color);
