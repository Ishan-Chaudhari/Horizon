#pragma once
#include <memory>
#include <tuple>
#include "Window.h"
#include "LayerStack.h"

#define LOG(x) std::cout << x << std::endl;

class Application
{
public:
	Application();
	virtual ~Application();
	void Initialize();
	void Run();
	void Terminate();
	void SetAppData(int window_width, int window_height, const char* window_title);
	void UpdateWindowDimensions(int width, int height);
	static std::tuple<int, int, const char*> GetWindowProps();
private:
	static std::tuple<int, int, const char*> WindowProps;
	std::unique_ptr<Window> window;
	std::unique_ptr<LayerStack> layerstack;
public:
	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
};

