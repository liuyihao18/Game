/**
 * 这个文件是游戏对象的源文件
 * 游戏对象的逻辑管理实现在这，控制玩家、敌人或者子弹等
 */

#include "stdafx.h"

#include "scene.h"
#include "object.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"

// 创建游戏物体
static void CreateGameObjects_StartScene();
static void CreateGameObjects_GameScene();

// 销毁游戏物体
static void DestroyGameObjects_StartScene();
static void DestroyGameObjects_GameScene();

// 更新游戏物体
static void UpdateGameObjects_StartScene(double deltaTime);
static void UpdateGameObjects_GameScene(double deltaTime);

// 渲染游戏物体
static void RenderGameObjects_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
static void RenderGameObjects_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

void InitGameObjects()
{
    // 初始化玩家对象
    InitPlayer();
    // 初始化敌人对象
    InitEnemy();
    // 初始化子弹对象
    InitBullet();

    // TODO: 游戏对象管理中需要在初始化阶段做的事情
}

void CreateGameObjects()
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        CreateGameObjects_StartScene();
        break;
    case GameScene:
        CreateGameObjects_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void DestroyGameObjects()
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        DestroyGameObjects_StartScene();
        break;
    case GameScene:
        DestroyGameObjects_GameScene();
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void UpdateGameObjects(double deltaTime)
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        UpdateGameObjects_StartScene(deltaTime);
        break;
    case GameScene:
        UpdateGameObjects_GameScene(deltaTime);
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void RenderGameObjects(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    switch (GetCurrentScene()->sceneId)
    {
    case None:
        break;
    case StartScene:
        RenderGameObjects_StartScene(hdc_memBuffer, hdc_loadBmp);
        break;
    case GameScene:
        RenderGameObjects_GameScene(hdc_memBuffer, hdc_loadBmp);
        break;
        // TODO: 更多的游戏场景
    default:
        break;
    }
}

void CreateGameObjects_StartScene()
{
    // TODO: 开始场景加载时需要创建的游戏对象
}

void CreateGameObjects_GameScene()
{
    // 初始化玩家对象
    CreatePlayer();
    // 敌人将在游戏过程中动态创建
    // 子弹将在游戏过程中动态创建
    // TODO: 游戏场景加载时需要创建的游戏对象
}

void DestroyGameObjects_StartScene()
{
    // TODO: 开始场景卸载时需要销毁的游戏对象
}

void DestroyGameObjects_GameScene()
{
    // 清空角色对象
    DestroyPlayer();
    // 清空敌人对象
    DestroyEnemies();
    // 清空子弹对象
    DestroyBullets();
    // TODO: 游戏场景卸载时需要销毁的游戏对象
}

void UpdateGameObjects_StartScene(double deltaTime)
{
    // TODO: 开始场景中需要更新的游戏对象
}

void UpdateGameObjects_GameScene(double deltaTime)
{
    // 更新角色对象
    UpdatePlayer(deltaTime);
    // 更新敌人对象
    UpdateEnemies(deltaTime);
    // 更新子弹对象
    UpdateBullets(deltaTime);
    // TODO: 游戏场景中需要更新的游戏对象
}

void RenderGameObjects_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // TODO: 开始场景中需要渲染的游戏对象
}

void RenderGameObjects_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制角色对象
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
    // 绘制敌人对象
    RenderEnemies(hdc_memBuffer, hdc_loadBmp);
    // 绘制子弹对象
    RenderBullets(hdc_memBuffer, hdc_loadBmp);
    // TODO: 游戏场景中需要渲染的游戏对象
}
