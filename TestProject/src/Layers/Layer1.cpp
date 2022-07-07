#include "Layer1.h"
#include "DirectX/DirectX11.h"

void Layer1::OnAttach()
{
	float vertices[] =
	{
		-0.5f,-0.5f, 0.f,1.f,0.f,
		-0.5f, 0.5f, 0.f,1.f,0.f,
		 0.5f, 0.5f, 0.f,1.f,0.f,
		 0.5f,-0.5f, 0.f,1.f,0.f,
	};
	unsigned int indices[] = { 0,1,2,2,3,0 };

	DirectX11::SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	vertexBuffer.Create(sizeof(vertices), vertices, sizeof(float) * 5, BufferType::HzVertexBuffer);
	vertexBuffer.Bind();

	VertexShader.Create(L"res/Shaders/VertexShader.cso",ShaderType::Vertex);
	VertexShader.Bind();

	PixelShader.Create(L"res/Shaders/PixelShader.cso",ShaderType::Pixel);
	PixelShader.Bind();

	VertexShaderLayout layout[] = 
	{
		{"POSITION",0,LayoutFormat::HZ_VEC2,LayoutType::PER_VERTEX},
		{"COLOR",2,LayoutFormat::HZ_VEC3,LayoutType::PER_VERTEX},
	};
	VertexShader.SetLayout(layout, 2);

	IndexBuffer.Create(sizeof(indices), indices, sizeof(unsigned int), BufferType::HzIndexBuffer);
	IndexBuffer.Bind();
	

}

void Layer1::OnUpdate()
{
	DirectX11::ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	DirectX11::GetContext()->DrawIndexed(IndexBuffer.GetCount(), 0, 0);

}

void Layer1::OnDetach()
{
}
