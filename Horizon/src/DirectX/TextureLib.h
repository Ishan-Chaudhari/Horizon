#pragma once
#include <unordered_map>
#include "Resource.h"

class TextureLib
{
private:
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
public:
	static void Create2D(const char* TexturePath, const char* TextureName);
	static void Bind(const char* TextureName);
	static void DestroyTexture(const char* TextureName);
private:
	static std::unordered_map<const char*,Texture*> TexLib;
};

