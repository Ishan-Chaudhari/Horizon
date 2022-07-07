#pragma once
#include "Resource.h"
#include <d3dcompiler.h>
#include "DirectX11.h"
#include "Core/Logger.h"
#include <xutility>

enum class LayoutFormat
{
	HZ_VEC1 = DXGI_FORMAT_R32_FLOAT,
	HZ_VEC2 = DXGI_FORMAT_R32G32_FLOAT,
	HZ_VEC3 = DXGI_FORMAT_R32G32B32_FLOAT,
	HZ_VEC4 = DXGI_FORMAT_R32G32B32A32_FLOAT,
	HZ_UINT1 = DXGI_FORMAT_R32_UINT,
};

enum class LayoutType
{
	PER_VERTEX = D3D11_INPUT_PER_VERTEX_DATA,
	PER_INSTANCE = D3D11_INPUT_PER_INSTANCE_DATA
};

struct VertexShaderLayout
{
	const char* SemanticName;
	UINT Offset;
	LayoutFormat format;
	LayoutType type;
};

class Shader
{
private:

public:
	void Create(LPCWSTR Filepath,ShaderType type);
	void Bind();
	void SetLayout(VertexShaderLayout layout[],int layoutcount);
private:
	HzVertexShader vshader;
	HzPixelShader pshader;
	HzBlob blob;
	ShaderType Type;
};
