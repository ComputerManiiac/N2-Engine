#include "GameApp.h"
#include "Manager.h"
#include "Core.h"

GameApp::GameApp(const char* name, unsigned int screenWidth, unsigned int screenHeight)
	: Application(name, screenWidth, screenHeight)
{
	
}

GameApp::GameApp()
{
}


GameApp::~GameApp()
{
	delete Manager::getInstance();
}



void GameApp::Run()
{

	Manager* m = Manager::getInstance();
	m->Initialize();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		m->Update();

		/* Clear all key down and release states */
		keyDown.clear();
		keyRelease.clear();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();
}

