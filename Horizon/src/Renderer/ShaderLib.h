#pragma once
#include <unordered_map>
#include "ShaderProgram.h"

class ShaderLib
{
public:
	static void CreateShaderProgram(LPCWSTR vsFilePath, LPCWSTR psFilePath, const char* ProgramName);
	static void BindProgram(const char* ProgramName);
	static void SetVertexLayout(VertexShaderLayout layout[], int count,const char* ProgramName);
	static void DestroyProgram(const char* ProgramName);
private:
	static std::unordered_map<const char*, ShaderProgram*> ProgramLib;
};

