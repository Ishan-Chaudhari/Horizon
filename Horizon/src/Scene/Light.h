#pragma once
#include "Math/DxMath.h"
#include "DirectX/ConstantBuffer.h"

class Light
{
	struct LightBuf
	{
		HzMath::Vector3 Position;
		HzMath::Vector3 Color;
		HzMath::Vector2 Dumb = { 0.f,0.f };
	};
public:
	Light();
	void Create();
	void Update();
	void UseLight();
	HzMath::Vector3 GetPosition() { return buf.Position; }
	void SetPosition(HzMath::Vector3 position);
	void SetColor(HzMath::Vector3 color);
private:
	LightBuf buf;
	ConstantBuffer ConstBuf;
};

