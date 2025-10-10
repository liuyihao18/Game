/**
 * 这个文件是敌人的源文件
 * 敌人AI等逻辑实现在这
 */

#include "stdafx.h"

#include "config.h"

#include "info.h"

#include "enemy.h"

static std::set<Enemy *> enemies;

static double lastGenerateTime = 0;
static double deltaGenerateTime = 3;

void InitEnemy()
{
    CreateRandomEnemy();
    lastGenerateTime = GetGameTime();
}

void CreateEnemy(double x, double y, int radius)
{
    Enemy *enemy = new Enemy();
    enemy->position = {x, y};
    enemy->radius = radius;
    enemies.insert(enemy);
}

void CreateRandomEnemy()
{
    CreateEnemy(
        120 + rand() * 0.8 / RAND_MAX * WINDOW_WIDTH,
        80 + rand() * 0.8 / RAND_MAX * WINDOW_HEIGHT,
        15);
}

void DestroyEnemy(Enemy *enemy)
{
    enemies.erase(enemy);
    delete enemy;
}

void DestroyEnemies()
{
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

std::vector<Enemy *> GetEnemies()
{
    return std::vector<Enemy *>(enemies.begin(), enemies.end());
}

void UpdateEnemies(double DeltaTime)
{
    // 每5秒在随机位置创建一个敌人
    double gameTime = GetGameTime();
    if (gameTime - lastGenerateTime > deltaGenerateTime)
    {
        CreateRandomEnemy();
        lastGenerateTime = gameTime;
    }

    // TODO: 更多的敌人逻辑
    for (Enemy *enemy : enemies)
    {
    }
}

void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 创建画笔和刷子
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));   // 蓝色画笔
    HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 255)); // 浅蓝填充

    // 选中画笔和刷子
    HPEN hOldPen = (HPEN)SelectObject(hdc_memBuffer, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc_memBuffer, hBrush);

    // 画出敌人
    for (Enemy *enemy : enemies)
    {
        Ellipse(hdc_memBuffer, (int)enemy->position.x, (int)enemy->position.y,
                (int)enemy->position.x + 2 * enemy->radius, (int)enemy->position.y + 2 * enemy->radius);
    }

    // 恢复原对象
    SelectObject(hdc_memBuffer, hOldPen);
    SelectObject(hdc_memBuffer, hOldBrush);

    // 删除新建对象
    DeleteObject(hPen);
    DeleteObject(hBrush);
}
