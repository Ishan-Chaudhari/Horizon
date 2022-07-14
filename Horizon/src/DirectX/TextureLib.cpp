#include "TextureLib.h"
#include "stb_image.h"
#include "DirectX11.h"
#include <iostream>

static int a = 0;

void TextureLib::Texture::Create2D(const char* TexturePath)
{
	stbi_set_flip_vertically_on_load(1);
	bufferData = stbi_load(TexturePath, &width, &height, &Channels, 4);

	D3D11_TEXTURE2D_DESC tdesc = {};
	tdesc.Width = width;
	tdesc.Height = height;
	tdesc.MipLevels = 1;
	tdesc.ArraySize = 1;
	tdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	tdesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tdesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA tsdesc = {};
	tsdesc.pSysMem = bufferData;
	tsdesc.SysMemPitch = width * 4;
	tsdesc.SysMemSlicePitch = 0;

	DirectX11::GetDevice()->CreateTexture2D(&tdesc, &tsdesc, &ptexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC shDesc = {};
	shDesc.Format = tdesc.Format;
	shDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shDesc.Texture2D.MostDetailedMip = 0;
	shDesc.Texture2D.MipLevels = 1;

	DirectX11::GetDevice()->CreateShaderResourceView(ptexture.Get(), &shDesc, &pShaderResV);

	D3D11_SAMPLER_DESC sdesc = {};
	sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	DirectX11::GetDevice()->CreateSamplerState(&sdesc, &pSampler);

	stbi_image_free(bufferData);
}

void TextureLib::Texture::Bind()
{
	DirectX11::GetContext()->PSSetShaderResources(0, 1, pShaderResV.GetAddressOf());
	DirectX11::GetContext()->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}


std::unordered_map<const char*, TextureLib::Texture*> TextureLib::TexLib;

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
