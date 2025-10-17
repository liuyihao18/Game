/**
 * 场景2 - 游戏场景
 * 头文件定义函数原型
 */

#pragma once

 /* 场景核心函数 - 每个场景必须全部实现 */

// 加载场景
void LoadScene_GameScene();

// 卸载场景
void UnloadScene_GameScene();

// 处理UI输入
void ProcessUiInput_GameScene();

// 碰撞检测
void CheckCollision_GameScene();

// 更新场景
void UpdateScene_GameScene(double deltaTime);

// 渲染场景
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

/* 其他场景函数 - 建议用 static 关键字声明并定义在 cpp 函数里  */
