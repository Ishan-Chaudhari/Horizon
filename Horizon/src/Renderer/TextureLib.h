#pragma once
#include <unordered_map>
#include "DirectX/Texture.h"

class TextureLib
{
public:
	static void Create2D(const char* TexturePath, const char* TextureName);
	static void Bind(const char* TextureName);
	static void DestroyTexture(const char* TextureName);
private:
	static std::unordered_map<const char*,Texture*> TexLib;
};

