#pragma once
#include "Core/Layer.h"
#include "Scene/Scene.h"
#include "Math/Camera.h"
#include "Scene/Material.h"
#include "Scene/Light.h"

class Layer6 : public Layer
{
public:
	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;
private:
	Scene scene;
	Camera cam;
	Material* mat;
	Light* light;
	Transform* Tf;
private:
	void Initialize();
	void KeyboardInputs();
};

