# 游戏框架设计

从设计者的观点来看这个框架。

## 三大区域

![](images/framework.png)

如图所示，该游戏框架分为三大区域，分别是Win32应用程序部分、游戏框架部分和场景逻辑部分，下面逐一展开。

### Win32应用程序层

这一层是框架的最底层，调用Windows提供的API来进行窗口初始化操作，随后进入窗口事件循环，由操作系统知会应用程序发生的事件。

`WinMain`函数中的代码几乎都由Visual Studio在创建“Windows桌面应用程序”时自动生成，不需要过分关注。游戏框架仅在这个函数中增加了**底部状态栏**的初始化。`WinMain`函数在初始化后进入主消息循环。

`WinProc`函数是对操作系统各种事件的处理函数，在该函数中将控制权交由游戏框架部分。例如：

- `WM_CREATE`：窗口创建后会调用游戏初始化`GameInit`函数，并设置定时器
- `WM_TIMER`：定时器以固定间隔产生该定时事件，定时事件中会调用游戏主循环函数`GameLoop`
- `WM_PAINT`：绘图事件，在该事件中绘制游戏画面
- `WM_KEY_DOWN`、`WM_KEY_OUT`、`WM_MOUSEMOVE`、`WM_LBUTTONDOWN`、`WM_LBUTTONUP`：一系列键盘和鼠标事件，在对应事件中设置键鼠输入

这样，相当于有一个中间层来和Win32应用程序对接，控制游戏的运行，即“游戏的操作系统”。

### 游戏框架层

“游戏的操作系统”，负责游戏的运行管理。游戏的运行管理主要包括：

- `GameInit`：进行游戏时间初始化，游戏资源初始化`GameResourceInit`，以及发出切换游戏场景到第一个场景的指令。
- `GameLoop`：进行游戏时间的计算与缓存，然后把控制权交给场景，进行游戏场景循环更新`SceneLoop`，最后发出绘制图像的指令给操作系统。
- `GameRender`：进行游戏画面绘制准备，初始化缓存等，然后把控制权交给场景，进行场景绘制`RenderScene`，最后回收缓存、结束绘制。
- `keyboard.h`、`mouse.h`：这两个模块会缓存键鼠的输入，并提供读取的接口，这种实现方式，可以解决粘健和不跟手的问题。

游戏框架会适时把控制权交由场景，也就是我们实际写游戏逻辑的地方

### 场景逻辑层

场景逻辑层，编写每个场景的逻辑，核心就是每个场景`h`中定义的六个函数。

- `LoadScene`：在场景加载时应该做的初始化操作，比如创建一些对象、初始化一些变量等
- `UnloadScene`：在场景卸载时应该做的资源清理操作，比如销毁一些对象等
- `ProcessUiInput`：在场景循环开始的时候先判断当前的Ui操作，例如按钮点击等
- `CheckCollision`：在场景循环中接着判断当前场景中的游戏对象是否产生碰撞，如果碰撞应该跑什么逻辑
- `UpdateScene`：在场景循环中最后更新当前场景中的游戏对象，例如移动等
- `RenderScene`：在场景中如何绘制当前场景

这里的核心就是由`GameLoop`调用`SceneLoop`函数时发生的事情：

```cpp
// 场景循环
void SceneLoop(double deltaTime)
{
	if (_newSceneId != None)
	{
		// 卸载当前场景
		ROUTE_SCENE_FUNCTION(UnloadScene);
		// 切换场景ID
		currentScene->sceneId = _newSceneId;
		_newSceneId = None;
		// 加载新场景
		ROUTE_SCENE_FUNCTION(LoadScene);
	}

	// 先处理UI输入
	ROUTE_SCENE_FUNCTION(ProcessUiInput);

	// 再计算碰撞
	ROUTE_SCENE_FUNCTION(CheckCollision);

	// 然后运行游戏逻辑
	ROUTE_SCENE_FUNCTION_OneParam(UpdateScene, deltaTime);
}

// 渲染场景
void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
	ROUTE_SCENE_FUNCTION_TwoParam(RenderScene, hdc_memBuffer, hdc_loadBmp);
}
```

其中，`ROUTE_SCENE_FUNCTION`是一个宏函数：

```c++
// 宏函数 - 路由场景函数调用，如果有新的场景需要添加，在这里添加对应的 case 分支
#define ROUTE_SCENE_FUNCTION(FUNCTION_NAME) \
    switch (GetCurrentScene()->sceneId)     \
    {                                       \
    case None:                              \
        break;                              \
    case StartScene:                        \
        FUNCTION_NAME##_StartScene();       \
        break;                              \
    case GameScene:                         \
        FUNCTION_NAME##_GameScene();        \
        break;                              \
    default:                                \
        break;                              \
    }
```

## 场景

<img src="images/scene.png" style="width:90%;" />

在场景逻辑层跑逻辑的时候，会分为游戏对象和UI组件两个部分，如上图所示。

在场景逻辑层的六个函数中，都需要同时考虑游戏对象和UI组件两个部分（除了`ProcessUiInput`只针对Ui、`CheckCollision`只针对游戏对象外）

角色、敌人和子弹等都可以把逻辑写到对应的`cpp`文件里，让场景部分的代码更简洁一些。

例如对于游戏场景的更新函数：

```cpp
void UpdateScene_GameScene(double deltaTime)
{
    /* UI组件更新 */
    // 游戏场景暂时没有UI组件需要更新

    /* 游戏对象更新 */
    // 更新角色对象
    UpdatePlayer(deltaTime);
    // 更新敌人对象
    UpdateEnemies(deltaTime);
    // 更新子弹对象
    UpdateBullets(deltaTime);
    // TODO: 游戏场景中需要更新的游戏对象
}
```

## 总结

在以上三层抽象、场景划分的结构下，增加新的场景或者在场景中添加新的对象都会比较简单，不需要修改框架文件的内容。游戏逻辑将内聚在对应的场景文件内已经游戏对象内，逻辑更加清晰。

