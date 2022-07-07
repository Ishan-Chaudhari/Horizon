#include "DirectX11.h"
#include "Core/Application.h"
#include "Core/Logger.h"
#pragma comment(lib,"d3d11.lib")

HzDevice DirectX11::pDevice;
HzSwapChain DirectX11::pSwapChain;
HzContext DirectX11::pContext;
HzRenderTarget DirectX11::pRenderTarget;

void DirectX11::Initialize()
{
	CreateDeviceAndSwapchain();
	CreateRenderTargetView();

	auto [x, y, t] = Application::GetWindowProps();
	SetViewPort(0.f, 0.f, (float)x, (float)y, 0.f, 1.f);

}

void DirectX11::SwapBuffers()
{
	pSwapChain->Present(1, 0);
	pContext->OMSetRenderTargets(1, pRenderTarget.GetAddressOf(), nullptr);
}

void DirectX11::ClearColor(float r, float g, float b, float a)
{
	const float rgba[4] = { r,g,b,a };
	pContext->ClearRenderTargetView(pRenderTarget.Get(), rgba);
}

void DirectX11::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	pContext->IASetPrimitiveTopology(topology);
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
