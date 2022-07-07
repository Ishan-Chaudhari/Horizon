#include "LayerStack.h"
#include <algorithm>

void LayerStack::AttachLayers()
{
	for (auto& layer : stack)
	{
		layer->OnAttach();
	}
}

void LayerStack::UpdateLayers()
{
	for (auto& layer : stack)
	{
		layer->OnUpdate();
	}
}


void LayerStack::DetachLayers()
{
	for (auto& layer : stack)
	{
		layer->OnDetach();
		delete layer;
		auto it = std::find(stack.begin(), stack.end(), layer);
		stack.erase(it);
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	stack.emplace_back(layer);
}

void LayerStack::PopLayer(Layer* layer)
{
	layer->OnDetach();
	delete layer;
	auto it = std::find(stack.begin(), stack.end(), layer);
	stack.erase(it);
}
