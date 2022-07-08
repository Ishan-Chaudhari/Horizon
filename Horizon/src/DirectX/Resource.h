#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

#define Cptr(x) Microsoft::WRL::ComPtr<x>

typedef Cptr(ID3D11Device) HzDevice;
typedef Cptr(IDXGISwapChain) HzSwapChain;
typedef Cptr(ID3D11DeviceContext) HzContext;
typedef Cptr(ID3D11RenderTargetView) HzRenderTarget;
typedef Cptr(ID3D11DepthStencilView) HzDepthStencilView;
typedef Cptr(ID3D11DepthStencilState) HzDepthStencilState;
typedef Cptr(ID3D11BlendState) HzBlendState;
typedef Cptr(ID3D11RasterizerState) HzRasterizerState;

typedef Cptr(ID3D11Resource) HzResource;

typedef Cptr(ID3D11VertexShader) HzVertexShader;
typedef Cptr(ID3D11PixelShader) HzPixelShader;
typedef Cptr(ID3D11Buffer) HzBuffer;
typedef Cptr(ID3DBlob) HzBlob;
typedef Cptr(ID3D11InputLayout) HzInputLayout;
typedef Cptr(ID3D11Texture2D) HzTexture2D;
typedef Cptr(ID3D11ShaderResourceView) HzShaderResourceView;
typedef Cptr(ID3D11SamplerState) HzSamplerState;

typedef Cptr(ID3D11VertexShader) HzVertexShader;
typedef Cptr(ID3D11PixelShader) HzPixelShader;

enum class BufferType
{
	HzVertexBuffer = D3D11_BIND_VERTEX_BUFFER,
	HzIndexBuffer = D3D11_BIND_INDEX_BUFFER,
	HzPixelConstantBuffer,
	HzVertexConstantBuffer,
};

enum class ShaderType
{
	Vertex, Pixel
};

