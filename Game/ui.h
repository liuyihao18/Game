/**
 * 这个文件是游戏UI的头文件
 * 如果要添加新的UI或者修改UI相关的逻辑，修改在这里
 */
#pragma once

// 创建UI
void CreateUi();
// 销毁UI
void DestroyUi();
// 更新UI
void UpdateUi(double deltaTime);
// 渲染UI
void RenderUi(HDC hdc_memBuffer, HDC hdc_loadBmp);

// 处理UI输入
void ProcessUiInput();
