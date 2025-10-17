/**
 * 这个文件是场景管理的头文件
 * 需要添加新的游戏场景时，修改这个文件，请同时修改宏函数部分
 */

#pragma once

// 游戏场景
enum SceneId
{
    None = 0,       // 没有场景
    StartScene = 1, // 开始场景
    GameScene = 2   // 游戏场景
};

struct Scene
{
    SceneId sceneId; // 游戏场景的编号

    // TODO: 如果需要更多的场景信息，添加在这里
};

// 场景循环
void SceneLoop(double deltaTime);

// 渲染场景
void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

Scene *GetCurrentScene();

// 切换场景
void ChangeScene(SceneId newSceneId);

// 宏函数 - 路由场景函数调用，如果有新的场景需要添加，在这里添加对应的 case 分支
#define ROUTE_SCENE_FUNCTION(FUNCTION_NAME) \
    switch (GetCurrentScene()->sceneId)     \
    {                                       \
    case None:                              \
        break;                              \
    case StartScene:                        \
        FUNCTION_NAME##_StartScene();       \
        break;                              \
    case GameScene:                         \
        FUNCTION_NAME##_GameScene();        \
        break;                              \
    default:                                \
        break;                              \
    }

#define ROUTE_SCENE_FUNCTION_OneParam(FUNCTION_NAME, param1) \
    switch (GetCurrentScene()->sceneId)                      \
    {                                                        \
    case None:                                               \
        break;                                               \
    case StartScene:                                         \
        FUNCTION_NAME##_StartScene(param1);                  \
        break;                                               \
    case GameScene:                                          \
        FUNCTION_NAME##_GameScene(param1);                   \
        break;                                               \
    default:                                                 \
        break;                                               \
    }

#define ROUTE_SCENE_FUNCTION_TwoParam(FUNCTION_NAME, param1, param2) \
    switch (GetCurrentScene()->sceneId)                              \
    {                                                                \
    case None:                                                       \
        break;                                                       \
    case StartScene:                                                 \
        FUNCTION_NAME##_StartScene(param1, param2);                  \
        break;                                                       \
    case GameScene:                                                  \
        FUNCTION_NAME##_GameScene(param1, param2);                   \
        break;                                                       \
    default:                                                         \
        break;                                                       \
    }
