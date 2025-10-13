/**
 * 这个文件是游戏场景的源文件
 * 如果要添加新的游戏场景或者修改游戏场景相关的逻辑，修改在这里
 */

#include "stdafx.h"

#include "scene.h"
#include "object.h"
#include "ui.h"

// 当前游戏场景
static Scene *currentScene;

// 加载场景 - 请务必保证场景中的对象都正确创建了
static void LoadScene(SceneId newSceneId);

// 卸载场景 - 请务必保证场景中的对象都正确销毁了
static void UnloadScene(SceneId oldSceneId);

// 初始化场景
void InitScene(SceneId newSceneId)
{
    currentScene = new Scene();
    // 初始化游戏对象
    InitGameObjects();
    // 初始化UI
    InitUi();
    // 加载场景
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

// 更新场景
void UpdateScene(double deltaTime)
{
    // 更新游戏对象
    UpdateGameObjects(deltaTime);
}

// 渲染场景
void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制场景物体
    RenderGameObjects(hdc_memBuffer, hdc_loadBmp);
    // 绘制UI
    RenderUi(hdc_memBuffer, hdc_loadBmp);
}

// 加载场景
void LoadScene(SceneId newSceneId)
{
    // 修改当前场景
    currentScene->sceneId = newSceneId;
    // 创建游戏对象
    CreateGameObjects();
    // 创建UI
    CreateUi();
}

// 卸载场景
void UnloadScene(SceneId oldSceneId)
{
    // 销毁UI
    DestroyUi();
    // 销毁游戏对象
    DestroyGameObjects();
}
