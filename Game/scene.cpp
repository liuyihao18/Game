/**
 * 这个文件是游戏场景的源文件
 * 如果要添加新的游戏场景或者修改游戏场景相关的逻辑，修改在这里
 */

#include "stdafx.h"

#include "scene.h"
#include "ui.h"

#include "player.h"
#include "enemy.h"

// 当前游戏场景
static Scene *currentScene;

// 加载场景 - 请务必保证场景中的对象都正确创建了
static void LoadScene(SceneId newSceneId);
static void LoadScene_StartScene();
static void LoadScene_GameScene();

// 卸载场景 - 请务必保证场景中的对象都正确销毁了
static void UnloadScene(SceneId oldSceneId);
static void UnloadScene_StartScene();
static void UnloadScene_GameScene();

// 初始化场景
void InitScene(SceneId newSceneId)
{
    currentScene = new Scene();
    LoadScene(newSceneId);
}

// 修改场景
void ChangeScene(SceneId newSceneId)
{
    UnloadScene(currentScene->sceneId);
    LoadScene(newSceneId);
}

// 获取当前游戏场景
Scene *GetCurrentScene()
{
    return currentScene;
}

// 加载场景
void LoadScene(SceneId newSceneId)
{
    switch (newSceneId)
    {
    case None:
        break;
    case StartScene:
        LoadScene_StartScene();
        break;
    case GameScene:
        LoadScene_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }

    // 修改当前场景
    currentScene->sceneId = newSceneId;
    // 创建UI
    CreateUi();
}

// 卸载场景
void UnloadScene(SceneId oldSceneId)
{
    switch (oldSceneId)
    {
    case None:
        break;
    case StartScene:
        UnloadScene_StartScene();
        break;
    case GameScene:
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }

    // 销毁UI
    DestroyUi();
}

void LoadScene_StartScene()
{
    // TODO: 开始场景需要初始化的对象
}

void LoadScene_GameScene()
{
    // 初始化玩家对象
    InitPlayer();
    // 初始化敌人对象
    InitEnemy();
    // TODO: 游戏场景需要初始化的对象
}

void UnloadScene_StartScene()
{
    // TODO: 开始场景需要销毁的对象
}

void UnloadScene_GameScene()
{
    // 清空角色对象
    DestroyPlayer();
    // 清空敌人对象
    DestroyEnemies();
    // TODO: 游戏场景需要销毁的对象
}
