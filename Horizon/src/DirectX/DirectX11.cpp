#include "DirectX11.h"
#include "Core/Application.h"
#include "Core/Logger.h"
#pragma comment(lib,"d3d11.lib")
#include <comdef.h>

HzDevice DirectX11::pDevice;
HzSwapChain DirectX11::pSwapChain;
HzContext DirectX11::pContext;
HzRenderTarget DirectX11::pRenderTarget;
HzDepthStencilView DirectX11::pDepthStencilView;
HzBlendState DirectX11::pBlendState;
HzRasterizerState DirectX11::pCClockWcull;
HzRasterizerState DirectX11::pClockWcull;

void DirectX11::Initialize()
{
	CreateDeviceAndSwapchain();
	CreateRenderTargetView();
	CreateDepthStencilView();
	CreateBlendState();

	auto [x, y, t] = Application::GetWindowProps();
	SetViewPort(0.f, 0.f, (float)x, (float)y, 0.f, 1.f);

}

void DirectX11::SwapBuffers()
{
	pSwapChain->Present(1, 0);
	pContext->OMSetRenderTargets(1, pRenderTarget.GetAddressOf(), pDepthStencilView.Get());
}

void DirectX11::ClearColor(float r, float g, float b, float a)
{
	const float rgba[4] = { r,g,b,a };
	pContext->ClearRenderTargetView(pRenderTarget.Get(), rgba);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void DirectX11::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	pContext->IASetPrimitiveTopology(topology);
}

void DirectX11::EnableBlendState()
{
	float blendfactor[4] = { 0.95f,0.95f,0.95f,1.f };
	pContext->OMSetBlendState(pBlendState.Get(), blendfactor, 0xffffffff);
}

void DirectX11::DisableBlendState()
{
	pContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void DirectX11::SetViewPort(float x, float y, float width, float height, float zMin, float zMax)
{
	D3D11_VIEWPORT vs = {};
	vs.TopLeftX = x;
	vs.TopLeftY = y;
	vs.Width = width;
	vs.Height = height;
	vs.MinDepth = zMin;
	vs.MaxDepth = zMax;

	pContext->RSSetViewports(1, &vs);

}

void DirectX11::CreateDeviceAndSwapchain()
{
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	auto[width, height, title] = Application::GetWindowProps();

	DXGI_SWAP_CHAIN_DESC dSwapDesc = {};

	UINT SwapCreateFlags = 0;

#ifdef _DEBUG
	SwapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

	dSwapDesc.Windowed = true;
	dSwapDesc.Flags = 0;
	dSwapDesc.OutputWindow = Window::GetHandle();
	dSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dSwapDesc.SampleDesc.Count = 1;
	dSwapDesc.SampleDesc.Quality = 0;
	dSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dSwapDesc.BufferCount = 2;
	dSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dSwapDesc.BufferDesc.RefreshRate.Numerator = 0;
	dSwapDesc.BufferDesc.RefreshRate.Denominator = 0;
	dSwapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dSwapDesc.BufferDesc.Width = width;
	dSwapDesc.BufferDesc.Height = height;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, SwapCreateFlags, nullptr, 0, D3D11_SDK_VERSION,
		&dSwapDesc, &pSwapChain, &pDevice, nullptr, &pContext);
}

void DirectX11::CreateRenderTargetView()
{
	HzResource pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRenderTarget);

}

void DirectX11::CreateDepthStencilView()
{
	auto [x, y, t] = Application::GetWindowProps();

	HzTexture2D pDepthBuffer;

	D3D11_TEXTURE2D_DESC bdesc = {};
	bdesc.Width = x;
	bdesc.Height = y;
	bdesc.BindFlags = 0;
	bdesc.CPUAccessFlags = 0;
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	bdesc.Format = DXGI_FORMAT_D32_FLOAT;
	bdesc.MipLevels = 1;
	bdesc.ArraySize = 1;
	bdesc.SampleDesc.Count = 1;
	bdesc.SampleDesc.Quality = 0;

	pDevice->CreateTexture2D(&bdesc, nullptr, &pDepthBuffer);

	HzDepthStencilState pDSState;

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	pDevice->CreateDepthStencilView(pDepthBuffer.Get(), &dsvDesc, &pDepthStencilView);

}

void DirectX11::CreateBlendState()
{
	D3D11_RENDER_TARGET_BLEND_DESC rbtd;

	rbtd.BlendEnable = true;
	rbtd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rbtd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rbtd.BlendOp = D3D11_BLEND_OP_ADD;
	rbtd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rbtd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rbtd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rbtd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC bdesc = {};
	bdesc.AlphaToCoverageEnable = false;
	bdesc.RenderTarget[0] = rbtd;
	
	pDevice->CreateBlendState(&bdesc, &pBlendState);

	D3D11_RASTERIZER_DESC rdesc = {};
	rdesc.FillMode = D3D11_FILL_SOLID;
	rdesc.CullMode = D3D11_CULL_BACK;
	rdesc.FrontCounterClockwise = true;
	
	pDevice->CreateRasterizerState(&rdesc, &pCClockWcull);
	
	rdesc.FrontCounterClockwise = false;
	pDevice->CreateRasterizerState(&rdesc, &pClockWcull);
}
