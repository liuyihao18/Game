/**
 * 这个文件是游戏类型的头文件
 * 基本的共有类型定义在了这里
 */

#pragma once

// 二维向量
struct Vector2
{
    double x;
    double y;
};

// 矩形
struct Rect
{
    double left;
    double top;
    double right;
    double bottom;
};

// 圆
struct Circle
{
    Vector2 center;
    double radius;
};

// 状态
struct Attributes
{
    int health;
    int score;
    double speed;

    // TODO: 其他相关的状态数值
};
// 现在玩家和敌人共用一个状态结构体，需要的话可以拆成两个
