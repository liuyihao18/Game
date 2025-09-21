/**
 * 这个文件是键盘输入的头文件
 * 如果要添加新的键盘功能，修改在这里
 */

#pragma once

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44

// Windows应用程序框架的写入函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 游戏逻辑的读取函数
bool GetKeyDown(int keycode);
