#pragma once
#include "Resource.h"

class Texture
{
public:
	void Create2D(const char* TexturePath);
	void Bind();
private:
	int width, height, Channels;
	unsigned char* bufferData;
	HzTexture2D ptexture;
	HzShaderResourceView pShaderResV;
	HzSamplerState pSampler;
};

