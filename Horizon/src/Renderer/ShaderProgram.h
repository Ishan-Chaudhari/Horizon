#pragma once
#include "DirectX/Shader.h"

class ShaderProgram
{
public:
	void Create(LPCWSTR vsFileName, LPCWSTR psFileName);
	void Bind();
	void SetVertexLayout(VertexShaderLayout layout[], int count);
private:
	Shader vertexShader;
	Shader pixelShader;
};

