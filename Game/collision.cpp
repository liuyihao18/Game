/**
 * 这个文件是游戏碰撞检测的源文件
 * 所有的碰撞检测都实现在这里
 * 可以添加其他的碰撞检测方法
 */

#include "stdafx.h"

#include "scene.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"

// 检查角色和敌人的碰撞
static void GameCheckCollision_StartScene();
static void GameCheckCollision_GameScene();
static void GameCheckCollision_GameScene_Player_Enemies();
static void GameCheckCollision_GameScene_Enemies_Bullets();

// 工具函数：矩形与圆碰撞检测
static bool IsRectCircleCollision(Rect rect, Circle c);
// 工具函数：矩形与矩形碰撞检测
static bool IsRectRectCollision(Rect r1, Rect r2);

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
    // 玩家和敌人的碰撞
    GameCheckCollision_GameScene_Player_Enemies();
    // 敌人和子弹的碰撞
    GameCheckCollision_GameScene_Enemies_Bullets();

    // TODO: 更多的碰撞逻辑
}

// 检查角色和敌人的碰撞
void GameCheckCollision_GameScene_Player_Enemies()
{
    // 玩家用简单矩形表示
    Player *player = GetPlayer();
    Rect rect1{};
    rect1.left = player->position.x;
    rect1.right = player->position.x + player->width;
    rect1.top = player->position.y;
    rect1.bottom = player->position.y + player->height;
    // 敌人用简单矩形表示
    std::vector<Enemy *> enemies = GetEnemies();
    Rect rect2{};
    for (Enemy *enemy : enemies)
    {
        rect2.left = enemy->position.x;
        rect2.right = enemy->position.x + enemy->width;
        rect2.top = enemy->position.y;
        rect2.bottom = enemy->position.y + enemy->height;
        if (IsRectRectCollision(rect1, rect2))
        {
            // 碰撞后扣血、加分摧毁敌人
            player->attributes.health--;
            player->attributes.score += enemy->attributes.score;
            DestroyEnemy(enemy);
            if (player->attributes.health <= 0)
            {
                Log(1, TEXT("游戏结束！"));
                ChangeScene(SceneId::StartScene);
            }
        }
    }
}

// 检查角色和敌人的碰撞
void GameCheckCollision_GameScene_Enemies_Bullets()
{
    // 敌人用简单矩形表示
    std::vector<Enemy *> enemies = GetEnemies();
    Rect rect{};
    // 子弹用简单圆形表示
    std::vector<Bullet *> bullets = GetBullets();
    Circle circle{};
    for (Enemy *enemy : enemies)
    {
        rect.left = enemy->position.x;
        rect.right = enemy->position.x + enemy->width;
        rect.top = enemy->position.y;
        rect.bottom = enemy->position.y + enemy->height;
        for (Bullet *bullet : bullets)
        {
            circle.center = bullet->position;
            circle.radius = bullet->radius;
            if (IsRectCircleCollision(rect, circle))
            {
                // 碰撞后扣血、加分摧毁敌人和子弹
                enemy->attributes.health -= bullet->damage;
                if (enemy->attributes.health <= 0)
                {
                    GetPlayer()->attributes.score += enemy->attributes.score;
                    DestroyEnemy(enemy);
                }
                DestroyBullet(bullet);
            }
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

// 矩形与矩形碰撞检测
bool IsRectRectCollision(Rect r1, Rect r2)
{
    return !(r2.left > r1.right ||
             r2.right < r1.left ||
             r2.top > r1.bottom ||
             r2.bottom < r1.top);
}