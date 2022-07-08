#include "TestProject.h"
#include "EntryPoint.h"
#include "Layers/Layer1.h"
#include "Layers/Layer2.h"
#include "Layers/Layer3.h"

TestProject::TestProject()
{
	SetAppData(1280, 720, "Horizon");

	//PushLayer(new Layer1());
	//PushLayer(new Layer2());
	PushLayer(new Layer3());
}

TestProject::~TestProject()
{
	
}

Application* CreateApp()
{
	return new TestProject();
}