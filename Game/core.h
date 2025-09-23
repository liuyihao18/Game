/**
 * 这个文件是游戏核心逻辑的头文件
 * 除非你想要修改游戏逻辑结构，不然不需要改这个文件
 */

#pragma once

#include "framework.h"

/* 主计时器ID */
#define MAIN_TIMER 1

/* 游戏初始化函数 */
void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam);
void GameResourceInit(HWND hWnd, WPARAM wParam, LPARAM lParam);
void InitTQTimer(HWND hWnd);
void InitMMTimer(HWND hWnd);
void DeleteTQTimer();
void DeleteMMTimer();

/* 游戏主循环函数 */
void GameLoop(HWND hWnd);
void GameCheckCollision();         // 游戏碰撞检测
void GameUpdate(double deltaTime); // 游戏更新 - 相邻两帧的时间间隔，单位：秒

/* 游戏渲染函数 */
void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam);
