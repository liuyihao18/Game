/**
 * 这个文件是游戏逻辑更新的源文件
 * 所有游戏状态的更新，都需要写在这里
 */

#include "stdafx.h"

#include "scene.h"

#include "player.h"
#include "enemy.h"

static void GameUpdate_StartScene(double deltaTime);
static void GameUpdate_GameScene(double deltaTime);

// 游戏更新逻辑
void GameUpdate(double deltaTime)
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        GameUpdate_StartScene(deltaTime);
        break;
    case GameScene:
        GameUpdate_GameScene(deltaTime);
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void GameUpdate_StartScene(double deltaTime)
{
    // 开始场景暂无游戏逻辑

    // TODO: 更多的更新逻辑
}

void GameUpdate_GameScene(double deltaTime)
{
    // 更新角色
    UpdatePlayer(deltaTime);
    // 更新敌人
    UpdateEnemies(deltaTime);

    // TODO: 更多的更新逻辑
}