/**
 * ����ļ����ӵ���Դ�ļ�
 * �ӵ��߼�ʵ������
 */

#include "stdafx.h"

#include "bullet.h"

static std::set<Bullet*> bullets;

void InitBullet()
{
	// TODO: �ӵ���������Ҫ�ڳ�ʼ���׶���������
}

void CreateBullet(double x, double y, int damage, double speed)
{
	Bullet* bullet = new Bullet();
	bullet->position = { x, y };
	bullet->radius = BULLET_RADIUS;
	bullet->damage = damage;
	bullet->speed = speed;
	bullets.insert(bullet);
}

void DestroyBullet(Bullet* bullet)
{
	bullets.erase(bullet);
	delete bullet;
}

void DestroyBullets()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

std::vector<Bullet*> GetBullets()
{
	return std::vector<Bullet*>(bullets.begin(), bullets.end());
}

void UpdateBullets(double deltaTime)
{
	// TODO: ������ӵ��߼�
	for (Bullet* bullet : GetBullets())
	{
		// �ӵ������ƶ�
		bullet->position.y -= bullet->speed * deltaTime; 
		// ������Ļ���ӵ�ɾ��
		if (bullet->position.y + bullet->radius < -10)
		{
			DestroyBullet(bullet);
		}
	}
}

void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
	// ������ɫʵ�Ļ�ˢ
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc_memBuffer, hBrush);

	// ���û���Ϊ�գ�����߿�Ӱ��
	HPEN hPen = (HPEN)SelectObject(hdc_memBuffer, GetStockObject(NULL_PEN));
	
	// �����ӵ�
	for (Bullet* bullet : bullets)
	{
		Ellipse(
			hdc_memBuffer,
			(int)(bullet->position.x - bullet->radius),
			(int)(bullet->position.y - bullet->radius),
			(int)(bullet->position.x + bullet->radius),
			(int)(bullet->position.y + bullet->radius)
		);
	}

	// �ָ� GDI ����
	SelectObject(hdc_memBuffer, oldBrush);
	SelectObject(hdc_memBuffer, hPen);
	DeleteObject(hBrush);
}


