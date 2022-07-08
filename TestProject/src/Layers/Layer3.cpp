#include "Layer3.h"
#include "DirectX/DirectX11.h"
#include "Renderer/ShaderLib.h"
#include "Core/Input.h"

void Layer3::OnAttach()
{
	float vertices[] =
	{
		-0.5f,-0.5f,-0.5f, 1.f,0.f,0.f,
		-0.5f, 0.5f,-0.5f, 0.f,1.f,0.f,
		 0.5f, 0.5f,-0.5f, 0.f,0.f,1.f,
		 0.5f,-0.5f,-0.5f, 1.f,1.f,1.f,

		-0.5f,-0.5f, 0.5f, 1.f,0.f,0.f,
		-0.5f, 0.5f, 0.5f, 0.f,1.f,0.f,
		 0.5f, 0.5f, 0.5f, 0.f,0.f,1.f,
		 0.5f,-0.5f, 0.5f, 1.f,1.f,1.f,
	};
	unsigned int indices[] = 
	{
		0,1,2 , 2,3,0,
		3,2,6 , 6,7,3,
		7,6,5 , 5,4,7,
		4,5,1 , 1,0,4,
		1,5,6 , 6,2,1,
		4,0,3 , 3,7,4,
	};

	DirectX11::SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vertexBuffer.Create(sizeof(vertices), vertices, sizeof(float) * 6, BufferType::HzVertexBuffer);
	vertexBuffer.Bind();

	IndexBuffer.Create(sizeof(indices), indices, sizeof(unsigned int), BufferType::HzIndexBuffer);
	IndexBuffer.Bind();

	World = DirectX::XMMatrixIdentity();
	cam.Create();
	cam.CalculateWvp(World);

	ShaderLib::CreateShaderProgram(L"res/Shaders/VertexShader.cso", L"res/Shaders/PixelShader.cso", "BasicProgram");
	ShaderLib::BindProgram("BasicProgram");

	VertexShaderLayout layout[] =
	{
		{"POSITION",0,LayoutFormat::HZ_VEC3,LayoutType::PER_VERTEX},
		{"COLOR",3,LayoutFormat::HZ_VEC3,LayoutType::PER_VERTEX},
	};
	ShaderLib::SetVertexLayout(layout,2,"BasicProgram");

}

void Layer3::OnUpdate()
{
	cam.Update();
	cam.CalculateWvp(World);
	
	DirectX11::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	DirectX11::GetContext()->DrawIndexed(IndexBuffer.GetCount(), 0, 0);
}

void Layer3::OnDetach()
{
}
