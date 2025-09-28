/**
 * 这个文件是游戏核心逻辑的源文件
 * 除非你想要修改游戏逻辑结构，不然不需要改这个文件
 */

#include "stdafx.h"

#include "config.h"
#include "info.h"
#include "core.h"

#include "scene.h"
#include "mouse.h"
#include "button.h"

// 内部游戏时间：单位（ms）
static double gameTime = 0;

// 时间戳：单位（ms）
static double firstFrameTimestamp = 0;
static double lastFrameTimestamp = 0;
static double GetCurrentTimestamp();

// 帧率统计：单位（Hz）
static std::deque<double> deltaTimeHistory;
static size_t deltaTimeHistorySize = 120;
static double UpdateDeltaTime(double currentFps);
static double GetAverageDeltaTime();
static void ShowAverageFps();

// 游戏初始化
void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    firstFrameTimestamp = GetCurrentTimestamp();
    lastFrameTimestamp = firstFrameTimestamp;
    GameResourceInit(hWnd, wParam, lParam);
    InitScene(StartScene);
}

// 游戏帧循环
void GameLoop(HWND hWnd)
{
    // 游戏时间处理
    double currentFrameTimestamp = GetCurrentTimestamp();
    gameTime = currentFrameTimestamp - firstFrameTimestamp;
    double deltaTime = (currentFrameTimestamp - lastFrameTimestamp);
    lastFrameTimestamp = currentFrameTimestamp;
    UpdateDeltaTime(deltaTime);
    ShowAverageFps();

    // 先计算输入
    if (IsMouseLButtonDown())
    {
        PressButtons(GetMouseX(), GetMouseY());
    }

    // 再计算碰撞
    GameCheckCollision();

    // 然后运行游戏逻辑
    GameUpdate(deltaTime / 1000.0);

    // 最后进行渲染，实际的渲染函数是GameRender，只重绘画面部分
    RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    InvalidateRect(hWnd, &rect, FALSE);
}

// 获取当前游戏时间，单位（s）
double GetGameTime()
{
    return gameTime / 1000.0;
}

// 工具函数：获取当前时间戳
double GetCurrentTimestamp()
{
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);  // 每秒多少tick
    QueryPerformanceCounter(&counter); // 当前tick
    return (double)counter.QuadPart * 1000.0 / freq.QuadPart;
}

// 工具函数：更新FPS
double UpdateDeltaTime(double currentFps)
{
    deltaTimeHistory.push_back(currentFps);
    if (deltaTimeHistory.size() > deltaTimeHistorySize)
    {
        deltaTimeHistory.pop_front();
    }
    return GetAverageDeltaTime();
}

// 工具函数：获取平均FPS
double GetAverageDeltaTime()
{
    double sum = std::accumulate(deltaTimeHistory.begin(), deltaTimeHistory.end(), .0);
    return sum / deltaTimeHistory.size();
}

// 工具函数：显示FPS
void ShowAverageFps()
{
    static double lastShowTime = -1;
    // 控制刷新间隔
    if (GetGameTime() - lastShowTime < 1)
    {
        return;
    }
    lastShowTime = GetGameTime();
    double averageFps = 1000.0 / GetAverageDeltaTime();
    // 在状态栏位置0显示FPS
    Log(0, "FPS: %.1f", averageFps);
}
