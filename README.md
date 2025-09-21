# Game

基于Win32API开发的简单游戏框架，面向《程序设计基础》课程的大作业项目。

尽可能只用C语法，但一些框架代码用了C++标准库，同时建议大家学习一下`std::vector`的用法。

游戏框架只有一个主线程，按照以下顺序跑循环（`core.cpp`）：

- 输入处理（`keyboard.cpp`和`mouse.cpp`分别进行键盘和鼠标输入缓存，`button.cpp`中处理按钮的点击并调用回调函数）：
  - `bool GetKeyDown(int keycode);`
  - `bool IsMouseLButtonDown();`
  - `int GetMouseX();`
  - `int GetMouseY();`
  -  `void PressButtons(int mouseX, int mouseY)`

- 碰撞检测（`collision.cpp`）：
  -  `void GameCheckCollision(); `
  - `static void GameCheckCollision_{SceneId}();`

- 游戏逻辑更新（`update.cpp`）： 
  - `void GameUpdate(double deltaTime);`
  - `static vod GameUpdate_{SceneId}(double deltaTime);`

- 图像渲染（`render.cpp`）：
  - `void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam)`
  - `static void RenderScene_{SceneId}(HDC hdc_memBuffer, HDC hdc_loadBmp)`


游戏框架中有资源初始化函数（`resource.cpp`），处理静态资源的加载：

- `void GameResourceInit(HWND hWnd, WPARAM wParam, LPARAM lParam);`

游戏框架中有场景系统（`scene.cpp`），需要处理场景的加载和卸载：

- `void ChangeScene(SceneId newSceneId);`
- `Scene *GetCurrentScene();`
- `static void LoadScene(SceneId newSceneId);`
- `static void LoadScene_{SceneId}();`
- `static void UnloadScene(SceneId oldSceneId); `
- `static void UnloadScene_{SceneId}();`

游戏玩家（`player.cpp`）和敌人（`enemy.cpp`）进行了简单实现：

- 在场景加载的时候进行初始化：
  - `void Init{Type}();`

- 在需要的时候创建：
  - `void Create{Type}();`

- 在场景卸载的时候或需要的时候进行销毁：
  - `void Destroy{Type}(); `

- 在碰撞检测模块中实现了两者的碰撞逻辑：
  - `static void GameCheckCollision_GameScene_Player_Enemies();`

- 在游戏逻辑更新的时候进行更新：
  - `void Update{Type}(double DeltaTime);`

- 在图像渲染的时候进行渲染：
  - `void Render{Type}(HDC hdc_memBuffer, HDC hdc_loadBmp);`


