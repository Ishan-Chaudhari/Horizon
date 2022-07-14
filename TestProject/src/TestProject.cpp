#include "TestProject.h"
#include "EntryPoint.h"
#include "Layers/Layer6.h"

TestProject::TestProject()
{
	SetAppData(1280, 720, "Horizon");

	PushLayer(new Layer6());
	
}

TestProject::~TestProject()
{
	
}

Application* CreateApp()
{
	return new TestProject();
}