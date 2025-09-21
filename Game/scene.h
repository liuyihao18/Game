/**
 * 这个文件是游戏场景的头文件
 * 如果要添加新的游戏场景或者修改游戏场景相关的逻辑，修改在这里
 */

#pragma once

// 游戏场景
enum SceneId
{
    None = 0,       // 空场景
    StartScene = 1, // 开始场景
    GameScene = 2   // 游戏场景
};

struct Scene
{
    SceneId sceneId; // 游戏场景的编号

    // TODO: 如果需要更多的场景信息，添加在这里
};

// 初始化场景
void InitScene(SceneId newSceneId);
// 切换场景
void ChangeScene(SceneId newSceneId);
// 获取当前场景
Scene *GetCurrentScene();
