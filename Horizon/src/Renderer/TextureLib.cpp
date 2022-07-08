#include "TextureLib.h"

std::unordered_map<const char*, Texture*> TextureLib::TexLib;

void TextureLib::Create2D(const char* TexturePath, const char* TextureName)
{
	Texture* tex = new Texture();
	tex->Create2D(TexturePath);
	TexLib[TextureName] = tex;
}

void TextureLib::Bind(const char* TextureName)
{
	TexLib[TextureName]->Bind();
}

void TextureLib::DestroyTexture(const char* TextureName)
{
	delete TexLib[TextureName];
	TexLib.erase(TextureName);
}
