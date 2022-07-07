#include "TestProject.h"
#include "EntryPoint.h"
#include "Layers/Layer1.h"
#include "Layers/Layer2.h"

TestProject::TestProject()
{
	SetAppData(1280, 720, "Horizon");

	//PushLayer(new Layer1());
	PushLayer(new Layer2());
}

TestProject::~TestProject()
{
	
}

Application* CreateApp()
{
	return new TestProject();
}