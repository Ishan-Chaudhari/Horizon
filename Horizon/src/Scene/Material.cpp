#include "Material.h"
#include "Core/Logger.h"
Material::Material()
{
	buf.Color = { 0.5f,0.5f,0.5f };
	buf.Metallic = 32.f;
	buf.Specular = { 0.1f,0.1f,0.1f };
	buf.Roughness = 0.1f;
}

void Material::CreateMaterial()
{
	ConstBuffer.Create(sizeof(buf), &buf);
	ConstBuffer.BindtoPixelShader(0);
}

void Material::BindMaterial()
{
	ConstBuffer.BindtoPixelShader(0);
}

void Material::UpdateMaterial()
{
	ConstBuffer.Update(&buf);
}

void Material::SetColor(HzMath::Vector3 color)
{
	buf.Color = color;
}

void Material::SetSpecular(HzMath::Vector3 specular)
{
	buf.Specular = specular;
}

void Material::SetMetallic(float metallic)
{
	buf.Metallic = metallic;
}

void Material::SetRoughness(float roughness)
{
	buf.Roughness = roughness;
}
