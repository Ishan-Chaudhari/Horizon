#pragma once
#include "Math/DxMath.h"
#include "DirectX/ConstantBuffer.h"

class Material
{
	struct MatBuf
	{
		HzMath::Vector3 Color;
		HzMath::Vector3 Specular;
		HzMath::Vector1 Metallic;
		HzMath::Vector1 Roughness;
	};
public:
	Material();
	void CreateMaterial();
	void BindMaterial();
	void UpdateMaterial();
	void SetColor(HzMath::Vector3 color);
	void SetSpecular(HzMath::Vector3 specular);
	void SetMetallic(float metallic);
	void SetRoughness(float roughness);
private:
	MatBuf buf;
	ConstantBuffer ConstBuffer;
};

