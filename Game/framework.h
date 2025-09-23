/**
 * 这个文件是Windows框架头文件
 * 几乎所有的代码文件都需要包含该文件
 */

#pragma once

// #include "targetver.h"
#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#pragma comment(lib, "comctl32.lib") // 解决报错：无法解析的外部符号 __imp_InitCommonControlsEx
#pragma comment(lib, "Msimg32.lib") // 解决报错：无法解析的外部符号 __imp_TransparentBlt
#pragma comment(lib, "Winmm.lib") // 解决报错：无法解析的外部符号 __imp_timeSetEvent

// 资源文件
#include "resource.h"

// 打印日志
void Log(int pos, const char *message);
void Log(int pos, const TCHAR *message);

// 游戏时间函数
double GetGameTime(); // 获取当前游戏时间，单位：秒
