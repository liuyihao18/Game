/**
 * 这个文件是游戏类型的头文件
 * 基本的共有类型定义在了这里
 */

#pragma once

struct Vector2
{
    double x;
    double y;
};

struct Rect
{
    double left;
    double top;
    double right;
    double bottom;
};

struct Circle
{
    Vector2 center;
    double radius;
};
