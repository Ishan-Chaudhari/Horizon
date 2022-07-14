#pragma once
#include <unordered_map>
#include "Math/Camera.h"
#include "Transform.h"
#include "Material.h"
#include "Light.h"

typedef uint32_t Entity;

class Scene
{
public:
	Scene();
	Entity NewEntity();
private:
	uint32_t EntityIndex;
private:
	std::unordered_map<Entity, Transform*> Transforms;
	std::unordered_map<Entity, const char*> Models;
	std::unordered_map<Entity, Material*> Materials;
	Light* light;
	Camera* cam;
public:
	void AttachTransform(Entity entity, Transform* transform);
	void AttachModel(Entity entity, const char* ModelName);
	void AttachMaterial(Entity entity, Material* material);
public:
	void AttachCamera(Camera* camera);
	void AttachLight(Light* light);
	void RenderModels();
};
