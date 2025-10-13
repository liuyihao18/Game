/**
 * 这个文件是游戏UI的源文件
 * 如果要添加新的UI或者修改UI相关的逻辑，修改在这里
 */

#include "stdafx.h"

#include "mouse.h"
#include "button.h"

#include "scene.h"
#include "ui.h"

#include "player.h"

// 创建UI
static void CreateUi_StartScene();
static void CreateUi_GameScene();

// 销毁UI
static void DestroyUi_StartScene();
static void DestroyUi_GameScene();

// 渲染UI
static void RenderUi_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
static void RenderUi_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

void InitUi()
{
    // TODO: UI中需要在初始化阶段做的事情
}

void CreateUi()
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        CreateUi_StartScene();
        break;
    case GameScene:
        CreateUi_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void DestroyUi()
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        DestroyUi_StartScene();
        break;
    case GameScene:
        DestroyUi_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void RenderUi(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        RenderUi_StartScene(hdc_memBuffer, hdc_loadBmp);
        break;
    case GameScene:
        RenderUi_GameScene(hdc_memBuffer, hdc_loadBmp);
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void ProcessUiInput()
{
    if (IsMouseLButtonDown())
    {
        PressButtons(GetMouseX(), GetMouseY());
    }
}

void CreateUi_StartScene()
{
	// 创建按钮
    const int width = 300;
    const int height = 200;
    const int x = (WINDOW_WIDTH - width) / 2 - 10; // what the f**k offset to center this?
    const int y = 196;
	CreateButton("StartButton", x, y, width, height, RenderStartButton, OnStartButtonClick);
    // TODO: 开始场景其他需要创建的UI组件
}

void CreateUi_GameScene()
{
    // TODO: 游戏场景其他需要创建的组件
}

void DestroyUi_StartScene()
{
    // 清空按钮
    DestroyButtons();
    // TODO: 开始场景其他需要销毁的UI组件
}

void DestroyUi_GameScene()
{
    // TODO: 游戏场景其他需要销毁的UI组件
}

void RenderUi_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    /* 注意绘制顺序 */

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
    const int width = 800;
    const int height = 300;
    const int left = WINDOW_WIDTH / 2 - width / 2 - 10;
    const int top = 456;
    const int right = left + width;
    const int bottom = top + height;
    RECT rect = { left, top, right, bottom };
    // 绘制
    DrawText(hdc_memBuffer, TEXT("使用WASD或方向键控制飞机移动\n使用空格发射子弹\n\n请大家好好学习这个框架_(:зゝ∠)_"), -1, &rect, DT_CENTER);
    // 恢复原来的字体
    SelectObject(hdc_memBuffer, hOldFont);
    // 删除自定义字体以释放资源
    DeleteObject(hFont);

    // TODO: 开始场景其他需要绘制的UI组件
}

void RenderUi_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    /* 注意绘制顺序 */

    // 绘制一个边框表示游戏区域
    // 选择画笔颜色（边框颜色）
    HPEN hPen = CreatePen(PS_SOLID, GAME_BOARDER, RGB(0, 0, 0));
    HGDIOBJ oldPen = SelectObject(hdc_memBuffer, hPen);

    // 使用透明画刷防止填充
    HGDIOBJ oldBrush = SelectObject(hdc_memBuffer, GetStockObject(NULL_BRUSH));

    // 绘制矩形（仅边框）
    Rectangle(hdc_memBuffer, GAME_X, GAME_Y, GAME_WIDTH, GAME_HEIGHT);

    // 还原 GDI 对象
    SelectObject(hdc_memBuffer, oldBrush);
    SelectObject(hdc_memBuffer, oldPen);
    DeleteObject(hPen);

    // 绘制玩家的属性信息
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
    const int width = 300;
    const int height = 200;
    const int left = GAME_WIDTH;
    const int top = 80;
    const int right = left + width;
    const int bottom = top + height;
    RECT rect = { left, top, right, bottom };
    // 绘制
    TCHAR buffer[128];
    swprintf_s(buffer, sizeof(buffer) / sizeof(TCHAR), 
        TEXT("第一关\n\n\n生命值: %d\n\n积分: %d"), 
        GetPlayer()->attributes.health,
        GetPlayer()->attributes.score
    );
    DrawText(hdc_memBuffer, buffer, -1, &rect, DT_CENTER);
    // 恢复原来的字体
    SelectObject(hdc_memBuffer, hOldFont);
    // 删除自定义字体以释放资源
    DeleteObject(hFont);

    // TODO: 游戏场景其他需要绘制的UI组件
}
