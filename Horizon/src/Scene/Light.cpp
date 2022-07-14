#include "Light.h"

Light::Light()
{
	buf.Position = { 0.f,0.f,0.f };
	buf.Color = { 0.5f,0.3f,0.2f };
}

void Light::Create()
{
	ConstBuf.Create(sizeof(buf), &buf);
	ConstBuf.BindtoPixelShader(1);
}

void Light::Update()
{
	ConstBuf.Update(&buf);
}

void Light::UseLight()
{
	ConstBuf.BindtoPixelShader(1);
}

void Light::SetPosition(HzMath::Vector3 position)
{
	buf.Position = position;
}

void Light::SetColor(HzMath::Vector3 color)
{
	buf.Color = color;
}

