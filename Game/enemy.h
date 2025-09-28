/**
 * 这个文件是敌人的头文件
 * 敌人逻辑实现在这
 */

#pragma once

#include "type.h"

struct Enemy
{
    Vector2 position;
    int radius;

    // TODO: 加入更多的敌人信息
};

// 初始化敌人
void InitEnemy();
// 创建敌人
void CreateEnemy(double x, double y, int radius);
void CreateRandomEnemy();
// 摧毁敌人
void DestroyEnemy(Enemy *enemy);
void DestroyEnemies();
// 获取所有敌人
std::vector<Enemy *> GetEnemies();
// 更新所有敌人
void UpdateEnemies(double DeltaTime);
// 渲染所有敌人
void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp);
