/**
 * 这个文件是子弹的源文件
 * 子弹逻辑实现在这
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
	return std::vector<Bullet *>(bullets.begin(), bullets.end());
}

void UpdateBullets(double deltaTime)
{
	// TODO: 更多的子弹逻辑
	for (Bullet *bullet : GetBullets())
	{
		// 子弹向上移动
		bullet->position.y -= bullet->speed * deltaTime;
		// 超出屏幕的子弹删除
		if (bullet->position.y + bullet->radius < 0)
		{
			DestroyBullet(bullet);
		}
	}
}

void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
	// 创建红色实心画刷
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc_memBuffer, hBrush);

	// 设置画笔为空，避免边框影响
	HPEN hPen = (HPEN)SelectObject(hdc_memBuffer, GetStockObject(NULL_PEN));

	// 绘制子弹
	for (Bullet *bullet : bullets)
	{
		Ellipse(
			hdc_memBuffer,
			(int)(bullet->position.x - bullet->radius),
			(int)(bullet->position.y - bullet->radius),
			(int)(bullet->position.x + bullet->radius),
			(int)(bullet->position.y + bullet->radius));
	}

	// 恢复 GDI 对象
	SelectObject(hdc_memBuffer, oldBrush);
	SelectObject(hdc_memBuffer, hPen);
	DeleteObject(hBrush);
}
