#pragma once
#include "Core/Layer.h"
#include "DirectX/Buffer.h"
#include "Renderer/ShaderProgram.h"
#include "Math/Camera.h"


class Layer3 : public Layer
{
public:
	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;
private:
	Buffer vertexBuffer;
	Buffer IndexBuffer;
	HzMath::Matrix World;
	Camera cam;
	HzMath::Matrix Translation, Rotation, Scale;
};

