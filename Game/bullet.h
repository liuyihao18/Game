/**
 * ����ļ����ӵ���ͷ�ļ�
 * �ӵ��߼�ʵ������
 */

#pragma once

struct Bullet {
	Vector2 position;
	int radius;
	int damage;
	double speed;
};

// ��ʼ���ӵ�
void InitBullet();
// �����ӵ�
void CreateBullet(double x, double y, int damage, double speed);
// �ݻ��ӵ�
void DestroyBullet(Bullet* bullet);
void DestroyBullets();
// ��ȡ�����ӵ�
std::vector<Bullet*> GetBullets();
// ���������ӵ�
void UpdateBullets(double deltaTime);
// ��Ⱦ�����ӵ�
void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp);
