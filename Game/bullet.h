/**
 * 这个文件是子弹对象的头文件
 * 子弹对象的逻辑实现在这
 */

#pragma once

struct Bullet
{
	Vector2 position;
	int radius;
	int damage;
	double speed;
};

// 创建子弹
void CreateBullet(double x, double y, int damage, double speed);
// 摧毁子弹
void DestroyBullet(Bullet *bullet);
void DestroyBullets();
// 获取所有子弹
std::vector<Bullet *> GetBullets();
// 更新所有子弹
void UpdateBullets(double deltaTime);
// 渲染所有子弹
void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp);
