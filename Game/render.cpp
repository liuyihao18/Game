/**
 * 这个文件是游戏渲染的源文件
 * 所有视觉的更新，都需要写在这里
 */

#include "framework.h"
#include "scene.h"
#include "button.h"
#include "player.h"
#include "enemy.h"
#include "config.h"

extern HBITMAP bmp_WhiteBackground;
extern HBITMAP bmp_BlackBackground;
extern HBITMAP bmp_StartButton;

static void RenderScene_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
static void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

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

    // 绘制场景数据
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        RenderScene_StartScene(hdc_memBuffer, hdc_loadBmp);
        break;
    case GameScene:
        RenderScene_GameScene(hdc_memBuffer, hdc_loadBmp);
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }

    // 最后将所有的信息绘制到屏幕上
    BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

    // 回收资源所占的内存（非常重要）
    DeleteObject(blankBmp);
    DeleteDC(hdc_loadBmp);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);
}

void RenderScene_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制背景到缓存
    SelectObject(hdc_loadBmp, bmp_WhiteBackground);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 绘制所有的按钮
    RenderButtons(hdc_memBuffer, hdc_loadBmp);

    // 绘制提示文字
    // 创建一个字体，设置高度为 30（单位是逻辑单元）
    HFONT hFont = CreateFont(
        30,                       // 字体高度
        0,                        // 字体宽度（0 表示自动计算）
        0,                        // 字体的倾斜角度
        0,                        // 字体的基线倾斜角度
        FW_NORMAL,                // 字体的粗细
        FALSE,                    // 是否斜体
        FALSE,                    // 是否下划线
        FALSE,                    // 是否删除线
        DEFAULT_CHARSET,          // 字符集
        OUT_DEFAULT_PRECIS,       // 输出精度
        CLIP_DEFAULT_PRECIS,      // 剪裁精度
        DEFAULT_QUALITY,          // 输出质量
        DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
        TEXT("微软雅黑")          // 字体名称
    );
    // 选择自定义字体到设备上下文
    HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
    // 设置字体区域
    RECT rect = {400, 500, 800, 800};
    // 绘制
    DrawText(hdc_memBuffer, TEXT("使用WASD控制方块移动~\n撞击消灭圆圈吧！\n\n请大家好好学习这个框架_(:зゝ∠)_"), -1, &rect, DT_CENTER);
    // 恢复原来的字体
    SelectObject(hdc_memBuffer, hOldFont);
    // 删除自定义字体以释放资源
    DeleteObject(hFont);

    // TODO: 更多的内容绘制
}

void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制背景到缓存
    SelectObject(hdc_loadBmp, bmp_WhiteBackground);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 绘制玩家
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
    // 绘制敌人
    RenderEnemies(hdc_memBuffer, hdc_loadBmp);

    // TODO: 更多的内容绘制
}
