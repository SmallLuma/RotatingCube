//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "stdafx.h"

#include "CommonClass.h"
#include "ModelTest.h"
#include <cstdio>
#include "Cursor.h"
#include "Device.h"
#include "Optional.h"
#include "ObjectSet.h"
#include "DemoRotatingCube.h"
#include "MainBackground.h"
#include "Cursor.h"
#include <Windows.h>
#include "RotatingCube.h"
#include "ObjModel.h"
#include "GameMain.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundEffect.h"


static Engine::ObjectSet<Engine::GameObject> root;

///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////

static Engine::Cursor& GetMouseCursor()
{
	static Engine::Cursor cur;
	return cur;
}

namespace Engine
{
	void ShowCursor(bool b)
	{
		b ?
			GetMouseCursor().Show() :
			GetMouseCursor().Hide();
	}
}

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	SDL_SetMainReady();

	// 初始化游戏引擎
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : 在此使用API更改窗口标题
	const std::string WindowTitle{ "Rotating Cube" };

	CSystem::SetWindowTitle(WindowTitle.c_str());

	const HWND hWnd = FindWindow("Darkstar Window Class", WindowTitle.c_str());

	SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8192);
	Game::SoundEffect::Init();

	Engine::InitDevice(hWnd, hInstance);
	auto& device = Engine::GetDevice();

	
	root.NewObject<Game::MainBackground>();
	//root.NewObject<Game::GamePlay::GameMain>(Game::GamePlay::Stages[5]);

	// 引擎主循环，处理屏幕图像刷新等工作
	while(device.EngineMainLoop())
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		const float	fTimeDelta	=	CSystem::GetTimeDelta();

		root.Update(fTimeDelta);
		root.Draw();

		GetMouseCursor().Update(fTimeDelta);
		GetMouseCursor().Draw();
	};

	Game::GamePlay::GameMain::ClearMusic();

	Game::SoundEffect::Quit();
	root.Clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	// 关闭游戏引擎
	CSystem::ShutdownGameEngine();

	return 0;
}


#pragma region Misc
#pragma warning(disable:4996)
extern "C"
{
	int _sprintf(char* buffer, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int r = sprintf(buffer, format, args);
		va_end(args);
		return r;
	}
};

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	

}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
//
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	// 可以在此添加游戏需要的响应函数
}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
//
void CSystem::OnKeyUp(const int iKey)
{
	// 可以在此添加游戏需要的响应函数
}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
//
void CSystem::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
	// 可以在此添加游戏需要的响应函数
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
//
void CSystem::OnSpriteColWorldLimit(const char *szName, const int iColSide)
{
	// 可以在此添加游戏需要的响应函数
}


#pragma endregion
