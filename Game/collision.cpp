/**
 * 这个文件是游戏碰撞检测的源文件
 * 所有的碰撞检测都实现在这里
 * 可以添加其他的碰撞检测方法
 */

#include "framework.h"
#include "core.h"
#include "scene.h"
#include "player.h"
#include "enemy.h"
#include <vector>

// 检查角色和敌人的碰撞
static void GameCheckCollision_StartScene();
static void GameCheckCollision_GameScene();
static void GameCheckCollision_GameScene_Player_Enemies();

// 工具函数：矩形与圆碰撞检测
static bool IsRectCircleCollision(Rect rect, Circle c);

// 检查全部的碰撞
void GameCheckCollision()
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        GameCheckCollision_StartScene();
        break;
    case GameScene:
        GameCheckCollision_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void GameCheckCollision_StartScene()
{
    // 开始场景暂无碰撞逻辑

    // TODO: 更多的碰撞逻辑
}

void GameCheckCollision_GameScene()
{
    GameCheckCollision_GameScene_Player_Enemies();

    // TODO: 更多的碰撞逻辑
}

// 检查角色和敌人的碰撞
void GameCheckCollision_GameScene_Player_Enemies()
{
    const Player *player = GetPlayer();
    std::vector<Enemy *> enemies = GetEnemies();
    for (Enemy *enemy : enemies)
    {
        Rect rect;
        rect.left = player->position.x;
        rect.right = player->position.x + player->width;
        rect.top = player->position.y;
        rect.bottom = player->position.y + player->height;
        Circle c;
        c.center.x = enemy->position.x + enemy->radius;
        c.center.y = enemy->position.y + enemy->radius;
        c.radius = enemy->radius;
        if (IsRectCircleCollision(rect, c))
        {
            // 碰撞后摧毁敌人
            DestroyEnemy(enemy);
        }
    }
}

// 矩形与圆碰撞检测
bool IsRectCircleCollision(Rect rect, Circle c)
{
    // clamp(cx, rect.left, rect.right)
    double closestX = max(rect.left, min(c.center.x, rect.right));
    double closestY = max(rect.top, min(c.center.y, rect.bottom));

    double dx = c.center.x - closestX;
    double dy = c.center.y - closestY;

    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}