#pragma once
#include "Resource.h"

class ConstantBuffer
{
public:
	void Create(int buffersize, void* buffer);
	void Update(void* buffer);
	void BindtoVertexShader(int slot);
	void BindtoPixelShader(int slot);
private:
	HzBuffer Buffer;
};

