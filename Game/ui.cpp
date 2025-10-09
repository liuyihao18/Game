/**
 * 这个文件是游戏UI的源文件
 * 如果要添加新的UI或者修改UI相关的逻辑，修改在这里
 */

#include "stdafx.h"

#include "scene.h"
#include "ui.h"

#include "button.h"

// 创建UI
static void CreateUi_StartScene();
static void CreateUi_GameScene();

// 销毁UI
static void DestroyUi_StartScene();
static void DestroyUi_GameScene();

// 渲染UI
static void RenderUi_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
static void RenderUi_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

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

void CreateUi_StartScene()
{
	// 创建按钮
	CreateButton("StartButton", 450, 222, 300, 200, RenderStartButton, OnStartButtonClick);
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
    RECT rect = { 400, 500, 800, 800 };
    // 绘制
    DrawText(hdc_memBuffer, TEXT("使用WASD控制方块移动~\n撞击消灭圆圈吧！\n\n请大家好好学习这个框架_(:зゝ∠)_"), -1, &rect, DT_CENTER);
    // 恢复原来的字体
    SelectObject(hdc_memBuffer, hOldFont);
    // 删除自定义字体以释放资源
    DeleteObject(hFont);

    // TODO: 开始场景其他需要绘制的UI组件
}

void RenderUi_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // TODO: 游戏场景其他需要绘制的UI组件
}
