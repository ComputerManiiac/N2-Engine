#include "GameApp.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "RenderSystem.h"
#include "Manager.h"

GameApp::GameApp(const char* name, unsigned int screenWidth, unsigned int screenHeight)
	: Application(name, screenWidth, screenHeight)
{

}

GameApp::GameApp()
{
}


GameApp::~GameApp()
{
}


void GameApp::Initialize()
{
	Application::Initialize();
}

void GameApp::Run()
{

	Manager* m = Manager::getInstance();
	Entity entity;
	RenderComponent* render = entity.getComponent<RenderComponent>();

	m->registerComponent<RenderSystem<RenderComponent>>(render);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{



		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

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

void GameApp::Deinitialize()
{
	Application::Deinitialize();
}