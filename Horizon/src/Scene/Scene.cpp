#include "Scene.h"
#include "DirectX/ModelLib.h"

Scene::Scene()
{
	EntityIndex = 0;
	cam = nullptr;
}

Entity Scene::NewEntity()
{
	return EntityIndex++;
}

void Scene::AttachTransform(Entity entity, Transform* transform)
{
	Transforms[entity] = transform;
}

void Scene::AttachModel(Entity entity, const char* ModelName)
{
	Models[entity] = ModelName;
}

void Scene::AttachMaterial(Entity entity, Material* material)
{
	Materials[entity] = material;
}

void Scene::AttachLight(Light* light)
{
	this->light = light;
}

void Scene::AttachCamera(Camera* camera)
{
	cam = camera;
}

void Scene::RenderModels()
{
	light->Update();
	for (auto& Model : Models)
	{
		Entity e = Model.first;
		cam->SetWvpBuffer(*Transforms[e]->GetTransform());
		Materials[e]->BindMaterial();
		ModelLib::RenderModel(Model.second);
	}
}

