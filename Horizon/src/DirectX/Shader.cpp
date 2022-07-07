#include "Shader.h"

#pragma comment(lib,"d3dcompiler.lib")

void Shader::Create(LPCWSTR Filepath, ShaderType type)
{
	D3DReadFileToBlob(Filepath, &blob);
	ASSERTPTR(blob, "ShaderParseFailed - " <<(const char*) Filepath);
	Type = type;
	if (Type==ShaderType::Vertex)
	{
		DirectX11::GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vshader);
	}
	else if (Type == ShaderType::Pixel)
	{
		DirectX11::GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pshader);
	}
	else
	{
		ASSERT(0, "Invalid Template Argument");
	}

}

void Shader::Bind()
{
	if (Type == ShaderType::Vertex)
	{
		DirectX11::GetContext()->VSSetShader(vshader.Get(), nullptr, 0);
	}
	else if (Type == ShaderType::Pixel)
	{
		DirectX11::GetContext()->PSSetShader(pshader.Get(), nullptr, 0);
	}
	else
	{
		ASSERT(0, "Invalid Template Argument");
	}
}

void Shader::SetLayout(VertexShaderLayout vlayout[], int layoutcount)
{
	if (Type != ShaderType::Vertex)
	{
		ASSERT(0, "Function Only applicable to Vertex Shader");
	}
	else
	{
		HzInputLayout layout;
		D3D11_INPUT_ELEMENT_DESC* indesc = new D3D11_INPUT_ELEMENT_DESC[layoutcount];

		for (int i = 0; i < layoutcount; i++)
		{
			indesc[i] = { vlayout[i].SemanticName,0,(DXGI_FORMAT)vlayout[i].format,0,(unsigned int)(vlayout[i].Offset * sizeof(float)),(D3D11_INPUT_CLASSIFICATION)vlayout[i].type,0 };
		}

		DirectX11::GetDevice()->CreateInputLayout(indesc, layoutcount, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);
		DirectX11::GetContext()->IASetInputLayout(layout.Get());

		delete[] indesc;
	}
}
