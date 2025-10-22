/**
 * 这个文件是子弹对象的源文件
 * 子弹对象的逻辑实现在这
 */

#include "stdafx.h"

#include "bullet.h"

static std::set<Bullet *> bullets;

void CreateBullet(double x, double y, int damage, double speed)
{
	Bullet *bullet = new Bullet();
	bullet->position.x = x;
	bullet->position.y = y;
	bullet->radius = BULLET_RADIUS;
	bullet->damage = damage;
	bullet->speed = speed;
	bullets.insert(bullet);
}

void DestroyBullet(Bullet *bullet)
{
	bullets.erase(bullet);
	delete bullet;
}

void DestroyBullets()
{
	for (Bullet *bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

std::vector<Bullet *> GetBullets()
{
	// 返回的是子弹指针的副本列表 - 避免边遍历边删除时出错
	return CopyFromSet(bullets);
}

void UpdateBullets(double deltaTime)
{
	// TODO: 子弹移动逻辑
}

void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
	// TODO: 绘制子弹
}
