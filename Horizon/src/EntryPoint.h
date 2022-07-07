#pragma once
#include "Core/Application.h"

extern Application* CreateApp();

int main()
{
	auto app = CreateApp();

	app->Initialize();
	app->Run();
	app->Terminate();

	delete app;
}