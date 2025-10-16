/**
 * 这个文件是游戏对象的头文件
 * 游戏对象的逻辑管理实现在这，控制玩家、敌人或者子弹等
 */

#pragma once

// 初始化游戏物体管理系统
void InitGameObjects();
// 创建游戏物体
void CreateGameObjects();
// 摧毁游戏物体
void DestroyGameObjects();
// 更新所有游戏物体
void UpdateGameObjects(double deltaTime);
// 渲染所有游戏物体
void RenderGameObjects(HDC hdc_memBuffer, HDC hdc_loadBmp);
