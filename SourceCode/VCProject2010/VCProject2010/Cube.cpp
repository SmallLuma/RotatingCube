#include "stdafx.h"
#include "Cube.h"
#include <d3d11.h>
#include "Shaders.h"
#include "Device.h"

using namespace Engine::Rendering;
using namespace DirectX;
Game::EngineTests::Cube::Cube()
{
	ps_ = LoadPShader("Green");
	
	std::vector<VertexIn> v = 
	{
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.5f, 0.5f, 0.5f,0.5f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.5f, 0.5f, 0.5f,0.5f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.5f, 0.5f, 0.5f,0.5f), XMFLOAT2(0.5f, 0.5f) }
	};

	buf_ = VertexIn::CreateBuffer(v);
}

void Game::EngineTests::Cube::Update(float)
{
}

void Game::EngineTests::Cube::Draw() const
{
	auto& ctx = GetDevice().Context();
	ctx.PSSetShader(ps_.Get(), nullptr, 0);

	auto buf = buf_.Get();
	const UINT Zero[] = { 0 };

	ctx.IASetVertexBuffers(0, 1, &buf, Zero, Zero);
	ctx.Draw(3, 0);
}
