#pragma once
#include "Layer.h"
#include <vector>

class LayerStack
{
public:
	void AttachLayers();
	void UpdateLayers();
	void DetachLayers();
public:
	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
private:
	std::vector<Layer*> stack;
};

