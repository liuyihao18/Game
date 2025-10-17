/**
 * 这个文件是按钮的源文件
 * 按钮的管理实现这，按钮的逻辑实现在对应的场景文件中
 */

#include "stdafx.h"

#include "button.h"

static std::set<Button *> buttons;

void CreateButton(ButtonId buttonId, double x, double y, int width, int height, RenderButtonFunc render, OnButtonClickFunc onClick)
{
    // 已经存在同样ID的按钮，不能创建
    if (GetButton(buttonId))
    {
        return;
    }

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
    // 返回的是按钮指针的副本列表 - 避免边遍历边删除时出错
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
        pressedButton->onClick(pressedButton);
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
