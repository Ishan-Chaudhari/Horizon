#include "ShaderProgram.h"
#include <vector>
#include <sstream>
#include "Core/Logger.h"

void ShaderProgram::Create(LPCWSTR vsFilePath, LPCWSTR psFilePath)
{
	vertexShader.Create(vsFilePath, ShaderType::Vertex);
	
	pixelShader.Create(psFilePath, ShaderType::Pixel);

}

void ShaderProgram::Bind()
{
	vertexShader.Bind();
	pixelShader.Bind();
}

void ShaderProgram::SetVertexLayout(VertexShaderLayout layout[], int count)
{
	vertexShader.Bind();
	vertexShader.SetLayout(layout, count);
}
