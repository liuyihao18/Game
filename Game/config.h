/**
 * 这个文件是游戏配置的头文件
 * 可以凭需求修改
 */

#pragma once

/* 游戏窗口位置与大小 */
#define WINDOW_X 150           // 游戏窗口位置X坐标
#define WINDOW_Y 100           // 游戏窗口位置Y坐标
#define WINDOW_WIDTH 1200      // 游戏窗口宽度
#define WINDOW_HEIGHT 800      // 游戏窗口高度
#define WINDOW_OTHER_HEIGHT 85 // 其他栏高度

/* 状态栏 */
const int statusBarParts[2] = {100, -1}; // 状态栏分栏，第一个分区宽度100，第二个占满剩余

/* 游戏内参数 */
#define FPS 100 // 游戏运行帧率，但是WIN32的定时器非常不准！
