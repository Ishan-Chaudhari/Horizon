#include "ShaderLib.h"
#include <algorithm>

std::unordered_map<const char*, ShaderProgram*> ShaderLib::ProgramLib;

void ShaderLib::CreateShaderProgram(LPCWSTR vsFilePath, LPCWSTR psFilePath, const char* ProgramName)
{
	ShaderProgram* Program = new ShaderProgram();
	Program->Create(vsFilePath, psFilePath);
	ProgramLib[ProgramName] = Program;
}

void ShaderLib::BindProgram(const char* ProgramName)
{
	ProgramLib[ProgramName]->Bind();
}

void ShaderLib::SetVertexLayout(VertexShaderLayout layout[], int count,const char* ProgramName)
{
	ProgramLib[ProgramName]->SetVertexLayout(layout, count);
}

void ShaderLib::DestroyProgram(const char* ProgramName)
{
	delete ProgramLib[ProgramName];
	ProgramLib.erase(ProgramName);
}
