#include "stdafx.h"
#include "direct2d.h"

#include "scene.h"
#include "scene3.h"
#include "mouse.h"

#include <cmath>
#include <deque>
#include <random>
#include <shared_mutex>

#define MAX_NUM 10000

struct Ball {
	double posx, posy, vy;
	float radius;
	Ball(double posx, double posy, double vy, float radius) :
		posx(posx),
		posy(posy),
		vy(vy),
		radius(radius) {
	}
};

static std::deque<std::shared_ptr<Ball>> balls;
static std::shared_mutex ball_mutex;
static ID2D1SolidColorBrush* pBrush = nullptr;
static const double g = 1000.0;

// 加载场景
void LoadScene_TestScene() {}

// 卸载场景
void UnloadScene_TestScene() {}

// 处理UI输入
void ProcessUiInput_TestScene() {
	if (IsMouseLButtonDown()) {
		std::unique_lock<std::shared_mutex> lock(ball_mutex);
		for (int i = 0; i < 10; i++) {
			balls.push_back(std::make_shared<Ball>(GetMouseX() + GetRandomDouble(-20.0, 20.0), 100.0, 0.0, (float)GetRandomDouble(1.0, 10.0)));
		}
		while (balls.size() > MAX_NUM) {
			balls.pop_front();
		}
		Log(2, "current count: %d", balls.size());
	}
}

// 碰撞检测
void CheckCollision_TestScene() {}

// 更新场景
void UpdateScene_TestScene(const double deltaTime) {
	std::unique_lock<std::shared_mutex> lock(ball_mutex);
	for (const auto& ptr : balls) {
		auto& ball = *ptr;
		double vy = ball.vy;
		double vy_new = vy + g * deltaTime;
		double posy_new = ball.posy + (vy + vy_new) * deltaTime / 2;
#define GROUND 700.0
		if (posy_new > GROUND) {
			posy_new = GROUND;
			vy_new = sqrt(vy * vy + 2 * g * (posy_new - ball.posy));
			double t1 = (vy_new - vy) / g;
			const double remainTime = deltaTime - t1;
			vy = -vy_new;

			vy_new = vy + g * remainTime;
			posy_new += (vy + vy_new) * remainTime / 2;
		}
		ball.vy = vy_new;
		ball.posy = posy_new;
	}
}

// 渲染场景，用于对比GDI性能
void RenderScene_TestScene(HDC hdc_memBuffer, HDC hdc_loadBmp) {
	std::shared_lock<std::shared_mutex> lock(ball_mutex);
	for (const auto pball : balls) {
		const auto& ball = *pball;
		Ellipse(hdc_memBuffer,
			(int)(ball.posx - ball.radius),
			(int)(ball.posy - ball.radius),
			(int)(ball.posx + ball.radius),
			(int)(ball.posy + ball.radius)
		);
	}
}

// 渲染场景：Direct2D
void D2DRenderScene_TestScene(ID2D1HwndRenderTarget* pRT) {
	if (pBrush == nullptr) {
		auto hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
		if (FAILED(hr)||pBrush==nullptr) {
			return;
		}
	}
	std::shared_lock<std::shared_mutex> lock(ball_mutex);
	for(const auto& ptr: balls) {
		const auto& ball = *ptr;
		pRT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((float)ball.posx, (float)ball.posy), ball.radius, ball.radius), pBrush);
	}
}
