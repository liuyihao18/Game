/**
 * 这个文件是玩家对象的源文件
 * 玩家对象的逻辑实现在这
 */

#include "stdafx.h"

#include "keyboard.h"

#include "player.h"
#include "bullet.h"

static Player *player;

// 渲染资源
extern HBITMAP bmp_Player;
static int frameIndex = 0;
static const int bmp_RowSize = 1;
static const int bmp_ColSize = 4;
static const int bmp_CellWidth = 200;
static const int bmp_CellHeight = 300;

void CreatePlayer()
{
    player = new Player();
    // TODO: 玩家初始位置
    // TODO: 玩家初始属性
}

void DestroyPlayer()
{
    delete player;
    player = nullptr;
}

Player *GetPlayer()
{
    return player;
}

void UpdatePlayer(double deltaTime)
{
    // TODO: 取键盘输入，然后控制角色位置（归一化方向向量，保证所有方向移动速度一致）
    
    // TODO: 归一化方向向量，保证所有方向移动速度一致

    // TODO: 限制角色在屏幕内

    // TODO: 发射子弹

    // TODO: 更新角色帧动画（假设1s播放完全部的动画）

    // TODO: 更多的角色逻辑
}

void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // TODO: 绘制玩家
}
