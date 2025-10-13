/**
 * 这个文件是游戏玩家的头文件
 * 玩家操作等逻辑实现在这
 */
#pragma once

#include "type.h"

// 玩家
struct Player
{
    Vector2 position;
    int width;
    int height;

    Attributes attributes;
};

// 初始化角色
void InitPlayer();
// 创建角色
void CreatePlayer();
// 删除角色
void DestroyPlayer();
// 获取角色
Player *GetPlayer();
// 更新角色
void UpdatePlayer(double deltaTime);
// 渲染角色
void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp);
