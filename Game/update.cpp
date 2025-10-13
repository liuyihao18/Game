/**
 * 这个文件是游戏逻辑更新的源文件
 * 所有游戏状态的更新，都需要写在这里
 */

#include "stdafx.h"

#include "scene.h"
#include "object.h"

// 游戏更新逻辑
void GameUpdate(double deltaTime)
{
    // 游戏场景中物体更新
    UpdateGameObjects(deltaTime);
}
