#pragma once
#include "Core/Layer.h"

#include "DirectX/Buffer.h"
#include "DirectX/Shader.h"

class Layer1 : public Layer
{
public:
	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;
private:
	Buffer vertexBuffer;
	Buffer IndexBuffer;
	Shader VertexShader;
	Shader PixelShader;
};

