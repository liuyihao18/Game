/**
 * 这个文件是游戏核心逻辑的源文件
 * 除非你想要修改游戏框架，否则不需要改这个文件
 */

#include "stdafx.h"

#include "core.h"
#include "scene.h"
#include "direct2d.h"

// 内部游戏时间：单位（ms）
static double gameTime = 0;
static double deltaTime = 0;

// 时间戳：单位（ms）
static double firstFrameTimestamp = 0;
static double lastFrameTimestamp = 0;
static double lastRenderTimestamp = 0;
static double GetCurrentTimestamp();

// 帧耗时统计：单位（ms）
static std::deque<double> deltaTimeHistory;
static std::deque<double> renderDeltaTimeHistory;
static size_t deltaTimeHistorySize = 120;
static void UpdateDeltaTime(std::deque<double>& history, double currentDeltaTime);
static double GetAverageDeltaTime(const std::deque<double>& history);
static void ShowAverageFps();
static void ShowAverageRenderFps();

// 游戏初始化
void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    firstFrameTimestamp = GetCurrentTimestamp();
    lastFrameTimestamp = firstFrameTimestamp;
    // 初始化游戏资源
    GameResourceInit(hWnd, wParam, lParam);
    // 切换到开始场景
    ChangeScene(TestScene);
}

// 游戏循环
void GameLoop(HWND hWnd)
{
    // 游戏时间处理
    double currentFrameTimestamp = GetCurrentTimestamp();
    gameTime = currentFrameTimestamp - firstFrameTimestamp;
    deltaTime = (currentFrameTimestamp - lastFrameTimestamp);
    lastFrameTimestamp = currentFrameTimestamp;
    UpdateDeltaTime(deltaTimeHistory, deltaTime);
    ShowAverageFps();

    // 场景循环更新
    SceneLoop();

    // 最后进行渲染，实际的渲染函数是GameRender，只重绘画面部分
#if TIMER_USE == WM_TIMER
    InvalidateRect(hWnd, nullptr, FALSE);
#else
    PostMessage(hWnd, WM_USER_PAINT, 0, 0);
#endif
}

// 渲染资源
extern HBITMAP bmp_WhiteBackground;

void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
#if RENDER_PIPELINE == RENDER_PIPELINE_GDI
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
    HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, blankBmp);

    // 清空背景
    SelectObject(hdc_loadBmp, bmp_WhiteBackground);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 绘制场景
    RenderScene(hdc_memBuffer, hdc_loadBmp);

    // 最后将所有的信息绘制到屏幕上
    BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

    // 回收资源所占的内存（非常重要）
    DeleteObject(blankBmp);
    DeleteDC(hdc_loadBmp);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);
#else RENDER_PIPELINE == RENDER_PIPELINE_D2D
    D2DRender(hWnd);
#endif
    // 渲染时间处理
    double currentTimestamp = GetCurrentTimestamp();
    double renderDeltaTime = (currentTimestamp - lastRenderTimestamp);
    lastRenderTimestamp = currentTimestamp;
    UpdateDeltaTime(renderDeltaTimeHistory, renderDeltaTime);
    ShowAverageRenderFps();
}

// 获取当前游戏时间（单位：s）
double GetGameTime()
{
    return gameTime / 1000.0;
}

// 获取两帧之间的时间差（单位：s）
double GetDeltaTime()
{
    return deltaTime / 1000.0;
}

// 工具函数：获取当前时间戳（单位：ms）
double GetCurrentTimestamp()
{
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);  // 每秒多少tick
    QueryPerformanceCounter(&counter); // 当前tick
    return (double)counter.QuadPart * 1000.0 / freq.QuadPart;
}

// 工具函数：更新帧耗时统计（单位：ms）
void UpdateDeltaTime(std::deque<double>& history, double currentDeltaTime)
{
    history.push_back(currentDeltaTime);
    if (history.size() > deltaTimeHistorySize)
    {
        history.pop_front();
    }
}

// 工具函数：获取平均帧耗时（单位：ms）
double GetAverageDeltaTime(const std::deque<double>& history)
{
    double sum = std::accumulate(history.begin(), history.end(), .0);
    return sum / history.size();
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
    double averageFps = 1000.0 / GetAverageDeltaTime(deltaTimeHistory);
    // 在状态栏位置0显示FPS
    Log(0, "Update FPS: %.1f", averageFps);
}

// 工具函数：显示渲染FPS
void ShowAverageRenderFps()
{
    static double lastShowTime = -1;
    // 控制刷新间隔
    if (GetGameTime() - lastShowTime < 1)
    {
        return;
    }
    lastShowTime = GetGameTime();
    double averageFps = 1000.0 / GetAverageDeltaTime(renderDeltaTimeHistory);
    // 在状态栏位置1显示FPS
    Log(1, "Render FPS: %.1f", averageFps);
}
