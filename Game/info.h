/**
 * 这个文件是信息头文件
 * 用以获取一些游戏信息或打印日志
 */

#pragma once

// 打印日志
void Log(int pos, const char* message);
void Log(int pos, const TCHAR* message);

// 游戏时间函数
double GetGameTime(); // 获取当前游戏时间，单位：秒
