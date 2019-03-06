#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GameApp.h"

int main(void)
{
	
	GameApp* game = new GameApp("N2 Engine", 1366, 768);
	game->Run();
	delete game;


	MemoryLeak::Dump();
	return 0;
}