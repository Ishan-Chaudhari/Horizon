#pragma once
#include "Resource.h"

class DirectX11
{
public:
	static void Initialize();
	static void SwapBuffers();
	static void ClearColor(float r, float g, float b, float a);
	static void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	static void EnableBlendState();
	static void DisableBlendState();
	static void SetViewPort(float x, float y, float width, float height, float zMin, float zMax);
private:
	static HzDevice pDevice;
	static HzSwapChain pSwapChain;
	static HzContext pContext;
	static HzRenderTarget pRenderTarget;
	static HzDepthStencilView pDepthStencilView;
	static HzBlendState pBlendState;
	static HzRasterizerState pClockWcull;
	static HzRasterizerState pCClockWcull;
public:
	static HzDevice GetDevice() { return pDevice; }
	static HzSwapChain GetSwapChain() { return pSwapChain; }
	static HzContext GetContext() { return pContext; }
	static HzRenderTarget GetRenderTarget() { return pRenderTarget; }
private:
	static void CreateDeviceAndSwapchain();
	static void CreateRenderTargetView();
	static void CreateDepthStencilView();
	static void CreateBlendState();
};

