﻿/**
 * 这个文件是敌人的源文件
 * 敌人AI等逻辑实现在这
 */

#include "stdafx.h"

#include "enemy.h"

static std::set<Enemy *> enemies;

// 渲染信息
extern HBITMAP bmp_Enemy;
static int frameIndex = 0;
static const int bmp_RowSize = 1;
static const int bmp_ColSize = 1;
static const int bmp_CellWidth = 200;
static const int bmp_CellHeight = 200;

// 上次产生时间
static double lastGenerateTime = 0;
static double deltaGenerateTime = 2;

void CreateEnemy(double x, double y)
{
    Enemy *enemy = new Enemy();
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->width = ENEMY_WIDTH;
    enemy->height = ENEMY_HEIGHT;
    enemy->attributes.health = 3;
    enemy->attributes.speed = 200;
    enemy->attributes.score = 1;
    enemies.insert(enemy);
}

void CreateRandomEnemy()
{
    CreateEnemy(
        GetRandomDouble(30, GAME_WIDTH - ENEMY_WIDTH - 30),
        -100 // 从上方稍微高一点的位置生成
    );
}

void DestroyEnemy(Enemy *enemy)
{
    enemies.erase(enemy);
    delete enemy;
}

void DestroyEnemies()
{
    for (Enemy *enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

std::vector<Enemy *> GetEnemies()
{
    return std::vector<Enemy *>(enemies.begin(), enemies.end());
}

void UpdateEnemies(double deltaTime)
{
    // 每隔一定时间在随机位置创建一个敌人
    double gameTime = GetGameTime();
    if (gameTime - lastGenerateTime > deltaGenerateTime)
    {
        CreateRandomEnemy();
        lastGenerateTime = gameTime;
    }

    // TODO: 更多的敌人逻辑
    for (Enemy *enemy : GetEnemies())
    {
        // 敌人向下移动
        enemy->position.y += enemy->attributes.speed * deltaTime;
        // 超出屏幕的敌人删除
        if (enemy->position.y > GAME_HEIGHT + 50)
        {
            DestroyEnemy(enemy);
        }
    }
}

void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 画出敌人
    const int frameRowIndex = frameIndex / bmp_ColSize;
    const int frameColIndex = frameIndex % bmp_ColSize;
    for (Enemy *enemy : enemies)
    {
        SelectObject(hdc_loadBmp, bmp_Enemy);
        TransparentBlt(
            hdc_memBuffer, (int)enemy->position.x, (int)enemy->position.y,
            enemy->width, enemy->height,
            hdc_loadBmp, frameColIndex * bmp_CellWidth, frameRowIndex * bmp_CellHeight, bmp_CellWidth, bmp_CellHeight,
            RGB(255, 255, 255));
    }
}
