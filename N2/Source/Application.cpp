#include "Application.h"

GLFWwindow* Application::window = nullptr;
std::map<int, bool> Application::keyDown = {};
std::map<int, bool> Application::keyRelease = {};

Application::Application(const char* name, unsigned int screenWidth, unsigned int screenHeight)
{
	this->name = name;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

Application::Application()
{
}


Application::~Application()
{
}

void Application::Initialize()
{

	/* Initialize the library */
	if (!glfwInit()) return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, name, NULL, NULL);
	if (!window) glfwTerminate();

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK){
		std::cout << "[ERROR] GLEW not initialized properly!" << std::endl;
		return;
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}

void Application::Run()
{
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

void Application::Deinitialize()
{

}

bool Application::isKeyPressed(int key)
{
	return glfwGetKey(window, key);
}

bool Application::isKeyPressDown(int key)
{
	return keyDown.find(key) != keyDown.end();
}

bool Application::isKeyPressRelease(int key)
{
	return keyRelease.find(key) != keyRelease.end();
}

void Application::keyCallback(GLFWwindow * window, int key, int scanNode, int action, int mods)
{

	/* Store key down and key release states of given key */

	if (action == GLFW_PRESS && keyDown.find(key) == keyDown.end())
		keyDown[key] = true;
	
	if (action == GLFW_RELEASE && keyRelease.find(key) == keyRelease.end())
		keyRelease[key] = true;
}

unsigned int Application::getScreenWidth()
{
	return screenWidth;
}

unsigned int Application::getScreenHeight()
{
	return screenHeight;
}
