/**
 * 这个文件是游戏按钮的源文件
 * 如果要添加新的按钮，添加在这里
 * 除非需要修改按钮相关的逻辑，不要修改核心代码
 */

#include "stdafx.h"

#include "button.h"

#include "scene.h"

#pragma region 按钮核心代码
static std::map<std::string, Button *> m;
static std::vector<Button *> buttons;

void CreateButton(const char *name, double x, double y, int width, int height, ButtonRenderFunc render, OnClickFunc onClick)
{
    Button *button = new Button();
    button->position = {x, y};
    button->width = width;
    button->height = height;
    button->render = render;
    button->isEnabled = true;
    button->onClick = onClick;

    m[name] = button;
    buttons.push_back(button);
}

void DestroyButton(const char *name)
{
    if (!m.count(name))
        return;

    Button *button = m[name];
    std::vector<Button *>::iterator iter = find(buttons.begin(), buttons.end(), button);
    buttons.erase(iter);
    m.erase(name);
    delete button;
}

void DestroyButtons()
{
    for (Button *button : buttons)
    {
        delete button;
    }
    m.clear();
    buttons.clear();
}

Button *GetButton(const char *name)
{
    if (!m.count(name))
        return nullptr;

    return m[name];
}

void EnableButton(const char *name)
{
    if (!m.count(name))
        return;

    Button *button = m[name];
    button->isEnabled = true;
}

void DisableButton(const char *name)
{
    if (!m.count(name))
        return;

    Button *button = m[name];
    button->isEnabled = false;
}

void PressButtons(int mouseX, int mouseY)
{
    Button *pressedButton = nullptr;
    for (std::vector<Button *>::reverse_iterator iter = buttons.rbegin(); iter != buttons.rend(); ++iter)
    {
        Button *button = *iter;
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
        button->render(hdc_memBuffer, hdc_loadBmp);
    }
}
#pragma endregion

extern HBITMAP bmp_StartButton;

void RenderStartButton(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    Button *button = GetButton("StartButton");

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
