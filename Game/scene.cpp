/**
 * 这个文件是游戏场景的源文件
 * 如果要添加新的游戏场景或者修改游戏场景相关的逻辑，修改在这里
 */

#include "stdafx.h"

#include "button.h"
#include "scene.h"
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
}

void LoadScene_StartScene()
{
    // 创建按钮
    CreateButton("StartButton", 450, 222, 300, 200, RenderStartButton, OnStartButtonClick);
}

void LoadScene_GameScene()
{
    // 初始化玩家
    InitPlayer();
    // 初始化敌人
    InitEnemy();
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
}

void UnloadScene_StartScene()
{
    // 清空按钮
    DestroyButtons();
}

void UnloadScene_GameScene()
{
    // 清空角色
    DestroyPlayer();
    // 清空敌人
    DestroyEnemies();
}
