#include "Application.h"
#include "Input.h"
#include "Logger.h"
#include "DirectX/DirectX11.h"

std::tuple<int, int, const char*> Application::WindowProps;

Application::Application()
{
	window = std::make_unique<Window>();
	layerstack = std::make_unique<LayerStack>();
}

void Application::Initialize()
{
	auto& [width, height, title] = WindowProps;
	window->Create(width, height, title);
	DirectX11::Initialize();
	layerstack->AttachLayers();
}

void Application::Run()
{
	while (window->IsOpen())
	{
		window->Update();
		if (Input::IsKeyPressed(VK_ESCAPE))
			window->Close();
		DirectX11::SwapBuffers();
		layerstack->UpdateLayers();
	}
}

void Application::Terminate()
{
	layerstack->DetachLayers();
	window->Shutdown();
}


Application::~Application()
{
	layerstack.reset();
	window.reset();
}

void Application::SetAppData(int window_width, int window_height, const char* window_title)
{
	WindowProps = std::make_tuple(window_width, window_height, window_title);
}

void Application::UpdateWindowDimensions(int width, int height)
{
	auto& [x, y, t] = WindowProps;
	WindowProps = std::make_tuple(width, height, t);
}

std::tuple<int, int, const char*> Application::GetWindowProps()
{
	return WindowProps;
}

void Application::PushLayer(Layer* layer)
{
	layerstack->PushLayer(layer);
}

void Application::PopLayer(Layer* layer)
{
	layerstack->PopLayer(layer);
}
