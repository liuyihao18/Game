/**
 * 这个文件是游戏按钮的头文件
 * 如果要添加新的按钮，添加在这里
 * 除非需要修改按钮相关的逻辑，不要修改核心代码
 */
#pragma once

#include "type.h"

// 按钮相关的定义
enum ButtonId
{
    StartButton = 0
};

// 这真的是纯C语言的内容
struct Button;
typedef void (*ButtonRenderFunc)(HDC hdc_memBuffer, HDC hdc_loadBmp);
typedef void (*OnClickFunc)(void);

struct Button
{
    Vector2 position; // 坐标 (x, y)
    int width;        // 宽度
    int height;       // 高度

    bool isEnabled;   // 是否激活

    ButtonRenderFunc render;
    OnClickFunc onClick;
};

// 按钮系统的对外函数
void CreateButton(const char* name, double x, double y, int width, int height, ButtonRenderFunc render, OnClickFunc onClick);
void DestroyButton(const char* name);
void DestroyButtons();
Button* GetButton(const char* name);
void EnableButton(const char* name);
void DisableButton(const char* name);
void PressButtons(int mouseX, int mouseY);
void RenderButtons(HDC hdc_memBuffer, HDC hdc_loadBmp);

// 实现每一个按钮的逻辑
void RenderStartButton(HDC hdc_memBuffer, HDC hdc_loadBmp);
void OnStartButtonClick();

// TODO: 加入更多的按钮逻辑
