#include "Layer6.h"
#include "DirectX/ModelLib.h"
#include "DirectX/ShaderLib.h"
#include "DirectX/DirectX11.h"
#include "Core/Input.h"

void Layer6::OnAttach()
{
	Initialize();

	cam.Create();
	scene.AttachCamera(&cam);

	Entity sphere = scene.NewEntity();
	Entity monkey = scene.NewEntity();
	Entity cube = scene.NewEntity();
	
	Tf = new Transform[3];
	mat = new Material[3];
	light = new Light();

	scene.AttachModel(monkey, "Monkey");
	scene.AttachTransform(monkey, &Tf[1]);
	scene.AttachMaterial(monkey, &mat[1]);

	scene.AttachModel(cube, "Cube");
	scene.AttachTransform(cube, &Tf[2]);
	scene.AttachMaterial(cube, &mat[2]);

	scene.AttachModel(sphere, "Sphere");
	scene.AttachTransform(sphere, &Tf[0]);
	scene.AttachMaterial(sphere, &mat[0]);

	mat[0].SetColor({ 1.f,0.f,0.f });
	mat[1].SetColor({ 0.f,1.f,0.f });
	mat[2].SetColor({ 0.5f,0.5f,1.f });

	float x = 0.f;
	for (int i = 0; i < 3; i++)
	{
		mat[i].CreateMaterial();
		Tf[i].SetPosition({ x,0.f,0.f });
		x += 2.f; 
	}

	scene.AttachLight(light);

	light->SetPosition({ 3.f,0.f,-5.f });
	light->SetColor({ 0.1f, 0.7f, 0.2f });
	light->Create();
	light->UseLight();
}
float d = 2.f;
void Layer6::OnUpdate()
{
	KeyboardInputs();
	cam.Update();

	if (Input::IsKeyPressed(VK_KEY_B))
	{
		Tf[0].SetRotation({ 0.f,1.f,0.f }, d); 
		d += 2.f;
	}
	if (Input::IsKeyPressed(VK_KEY_N))
	{
		Tf[0].SetRotation({ 0.f,1.f,0.f }, d); 
		d -= 2.f;
	}

	DirectX11::ClearColor(0.1f, 0.3f, 0.5f, 1.f);
	scene.RenderModels();
}

void Layer6::OnDetach()
{
	delete[] Tf;
	delete[] mat;
	delete light;

	ShaderLib::DestroyProgram("Phong");
	ModelLib::DestroyModel("Sphere");
	ModelLib::DestroyModel("Monkey");
	ModelLib::DestroyModel("Cube");
}

void Layer6::Initialize()
{
	DirectX11::SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ModelLib::LoadModel("res/Models/Monkey.obj", "Monkey");
	ModelLib::LoadModel("res/Models/cube.obj", "Cube");
	ModelLib::LoadModel("res/Models/Sphere.obj", "Sphere");

	ShaderLib::CreateShaderProgram(L"res/Shaders/cso/PhongVertex.cso", L"res/Shaders/cso/PhongPixel.cso", "Phong");
	ShaderLib::CreateShaderProgram(L"res/Shaders/cso/VertexShader.cso", L"res/Shaders/cso/PixelShader.cso", "Model");
	ShaderLib::BindProgram("Model");

	VertexShaderLayout layout[] =
	{
		{"POSITION",0,LayoutFormat::HZ_VEC3,LayoutType::PER_VERTEX},
		{"NORMAL",0,LayoutFormat::HZ_VEC3,LayoutType::PER_VERTEX},
		{"TEXC",0,LayoutFormat::HZ_VEC2,LayoutType::PER_VERTEX},
	};
	ShaderLib::SetVertexLayout(layout, 3, "Phong");
	ShaderLib::SetVertexLayout(layout, 3, "Model");
}

float sp = 0.02f;

void Layer6::KeyboardInputs()
{
	if (Input::IsKeyPressed(VK_KEY_K))
		DirectX11::EnableBlendState();
	if (Input::IsKeyPressed(VK_KEY_L))
		DirectX11::DisableBlendState();

	if (Input::IsKeyPressed(VK_KEY_P))
		ShaderLib::BindProgram("Phong");
	if (Input::IsKeyPressed(VK_KEY_O))
		ShaderLib::BindProgram("Model");

	if (Input::IsKeyPressed(VK_RIGHT))
		light->SetPosition({ light->GetPosition().x + sp,light->GetPosition().y,light->GetPosition().z });
	if (Input::IsKeyPressed(VK_LEFT))
		light->SetPosition({ light->GetPosition().x - sp,light->GetPosition().y,light->GetPosition().z });
	if (Input::IsKeyPressed(VK_UP))
		light->SetPosition({ light->GetPosition().x,light->GetPosition().y + sp,light->GetPosition().z });
	if (Input::IsKeyPressed(VK_DOWN))
		light->SetPosition({ light->GetPosition().x,light->GetPosition().y - sp,light->GetPosition().z });
	if (Input::IsKeyPressed(VK_SPACE))
		light->SetPosition({ light->GetPosition().x,light->GetPosition().y,light->GetPosition().z + sp });
	if (Input::IsKeyPressed(VK_BACKSPACE))
		light->SetPosition({ light->GetPosition().x,light->GetPosition().y,light->GetPosition().z - sp });
}
