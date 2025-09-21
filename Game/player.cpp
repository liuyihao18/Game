/**
 * 这个文件是游戏玩家的头文件
 * 玩家操作等逻辑实现在这
 */

#include "framework.h"
#include "player.h"
#include "keyboard.h"
#include "util.h"

static Player *player;

extern HBITMAP bmp_Player;
static int frameIndex = 0;
static const int bmp_RowSize = 1;
static const int bmp_ColSize = 4;
static const int bmp_CellWidth = 50;
static const int bmp_CellHeight = 50;

void InitPlayer()
{
    CreatePlayer();
}

void CreatePlayer()
{
    player = new Player();
    // 玩家初始位置
    player->position = { 550, 350 };
    player->width = 50;
    player->height = 50;
    // 玩家初始速度
    player->status.velocity = 500;
}

void DestroyPlayer()
{
    delete player;
}

Player *GetPlayer()
{
    return player;
}

void UpdatePlayer(double deltaTime)
{
    // 读取键盘输入，然后控制角色位置
    Vector2 direction = {0, 0};
    if (GetKeyDown(VK_W) || GetKeyDown(VK_UP))
    {
        direction.y -= 1;
    }
    if (GetKeyDown(VK_S) || GetKeyDown(VK_DOWN))
    {
        direction.y += 1;
    }
    if (GetKeyDown(VK_A) || GetKeyDown(VK_LEFT))
    {
        direction.x -= 1;
    }
    if (GetKeyDown(VK_D) || GetKeyDown(VK_RIGHT))
    {
        direction.x += 1;
    }
    direction = Normalize(direction);
    player->position.x += direction.x * player->status.velocity * deltaTime;
    player->position.y += direction.y * player->status.velocity * deltaTime;

    // 更新角色帧动画（假设1s播放完全部的动画）
    frameIndex = (int)(GetGameTime() * bmp_RowSize * bmp_ColSize) % (bmp_RowSize * bmp_ColSize);

    // TODO: 更多的角色逻辑
}

void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制玩家
    SelectObject(hdc_loadBmp, bmp_Player);
    const int frameRowIndex = frameIndex / bmp_ColSize;
    const int frameColIndex = frameIndex % bmp_ColSize;
    TransparentBlt(
        hdc_memBuffer, (int)player->position.x, (int)player->position.y,
        player->width, player->height,
        hdc_loadBmp, frameColIndex * bmp_CellWidth, frameRowIndex * bmp_CellHeight, bmp_CellWidth, bmp_CellHeight,
        RGB(255, 255, 255));
}
