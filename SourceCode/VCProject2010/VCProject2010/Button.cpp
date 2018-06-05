#include "stdafx.h"
#include "Button.h"

void Engine::Button::SetOnClick(const std::function<void()>& onClick)
{
	onClick_ = onClick;
}

void Engine::Button::Update(float time)
{
	alpha_.Update(time);
	zoom_.Update(time);
	posX_.Update(time);
	posY_.Update(time);

	SetPos(posX_, posY_);
	SetZoom(zoom_);
	SetAlpha(alpha_);

	
	bool mouseBtnDown;
	DirectX::XMFLOAT2 mousePos;
	std::tie(mouseBtnDown, mousePos) = Engine::GetDevice().Mouse();
	mousePos.x *= 800;
	mousePos.y *= 600;
	mousePos.x -= 400;
	mousePos.y -= 300;
	mousePos.y = -mousePos.y;

	auto spRect = GetSpriteRect();
	const bool mouseInRect =
		mousePos.x > spRect.x && mousePos.y > spRect.y &&
		mousePos.x < spRect.z && mousePos.y < spRect.w;

	const bool mode =
		mouseInRect ?
			(mouseBtnDown ?
				!mouseInRect :
				mouseInRect)
		:
			false;

	if (mode != lastMode)
	{
		lastMode = mode;

		zoom_.Run(mode ? 0.6F : 0.5F, 0.15F, 1);
	}

	if (mouseInRect && clickEnabled_ && lastMouseDown && !mouseBtnDown)
	{
		clickEnabled_ = false;
		onClick_();
	}

	lastMouseDown = mouseBtnDown;
}

void Engine::Button::SetEnable(bool b)
{
	clickEnabled_ = b;
}