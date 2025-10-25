#pragma once

// 加载场景
void LoadScene_TestScene();

// 卸载场景
void UnloadScene_TestScene();

// 处理UI输入
void ProcessUiInput_TestScene();

// 碰撞检测
void CheckCollision_TestScene();

// 更新场景
void UpdateScene_TestScene(double deltaTime);

// 渲染场景，占位符
void RenderScene_TestScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

// 渲染场景：Direct2D
void D2DRenderScene_TestScene(ID2D1HwndRenderTarget* pRT);