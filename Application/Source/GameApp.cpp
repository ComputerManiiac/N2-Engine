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
	StopWatch timer;
	timer.startTimer();
	timer.getElapsedTime();

	Manager* m = Manager::getInstance();
	m->Initialize();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		glClearColor(0.2f, 0.2f, 0.5f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Application::isKeyPressDown(GLFW_KEY_ESCAPE)){
			glfwSetWindowShouldClose(window, 1);
		}

		m->Update(timer.getElapsedTime());

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

