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
