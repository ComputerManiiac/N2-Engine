#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Utility.h"
#include "Application.h"

int main(void)
{
	


	Application* app = new Application("N2 Engine", 1366, 768);
	app->Initialize();
	app->Run();
	delete app;

	MemoryLeak::Dump();
	return 0;
}