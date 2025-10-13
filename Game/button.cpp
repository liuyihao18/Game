/**
 * 这个文件是游戏按钮的源文件
 * 如果要添加新的按钮，添加在这里
 * 除非需要修改按钮相关的逻辑，不要修改核心代码
 */

#include "stdafx.h"

#include "button.h"

#include "scene.h"

#pragma region 按钮核心代码

static std::set<Button *> buttons;

void InitButton()
{
    // TODO: 按钮管理中需要在初始化阶段做的事情
}

void CreateButton(ButtonId buttonId, double x, double y, int width, int height, RenderButtonFunc render, OnButtonClickFunc onClick)
{
    Button *button = new Button();

    button->buttonId = buttonId;

    button->position.x = x;
    button->position.y = y;
    button->width = width;
    button->height = height;

    button->isEnabled = true;

    button->render = render;
    button->onClick = onClick;

    buttons.insert(button);
}

void DestroyButton(ButtonId buttonId)
{
    if (Button *button = GetButton(buttonId))
    {
        buttons.erase(button);
        delete button;
    }
}

void DestroyButtons()
{
    for (Button *button : buttons)
    {
        delete button;
    }
    buttons.clear();
}

std::vector<Button *> GetButtons()
{
    return std::vector<Button *>(buttons.begin(), buttons.end());
}

Button *GetButton(ButtonId buttonId)
{
    for (Button *button : buttons)
    {
        if (button->buttonId == buttonId)
        {
            return button;
        }
    }

    return nullptr;
}

void EnableButton(ButtonId buttonId)
{
    if (Button *button = GetButton(buttonId))
    {
        button->isEnabled = true;
    }
}

void DisableButton(ButtonId buttonId)
{
    if (Button *button = GetButton(buttonId))
    {
        button->isEnabled = false;
    }
}

void PressButtons(int mouseX, int mouseY)
{
    // 注意：如果有按钮重叠，点击结果是不确定的！
    Button *pressedButton = nullptr;
    for (Button *button : buttons)
    {
        if (!button->isEnabled)
        {
            continue;
        }
        if (button->position.x <= mouseX &&
            button->position.x + button->width >= mouseX &&
            button->position.y <= mouseY &&
            button->position.y + button->height >= mouseY)
        {
            pressedButton = button;
            break;
        }
    }
    if (pressedButton)
    {
        pressedButton->onClick();
    }
}

void RenderButtons(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    for (Button *button : buttons)
    {
        if (!button->isEnabled)
        {
            continue;
        }
        button->render(button, hdc_memBuffer, hdc_loadBmp);
    }
}
#pragma endregion

extern HBITMAP bmp_StartButton;

void RenderStartButton(Button *button, HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    SelectObject(hdc_loadBmp, bmp_StartButton);
    TransparentBlt(
        hdc_memBuffer, (int)button->position.x, (int)button->position.y,
        button->width, button->height,
        hdc_loadBmp, 0, 0, button->width, button->height,
        RGB(255, 255, 255));
}

void OnStartButtonClick()
{
    Log(1, TEXT("游戏开始！"));
    ChangeScene(SceneId::GameScene);
}

// TODO: 加入更多的按钮逻辑
