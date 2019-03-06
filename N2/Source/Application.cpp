#include "Application.h"

GLFWwindow* Application::window = nullptr;
std::map<int, bool> Application::keyDown = {};
std::map<int, bool> Application::keyRelease = {};

double Application::mouseX = 0.0;
double Application::mouseY = 0.0;

unsigned int Application::screenWidth = 0;
unsigned int Application::screenHeight = 0;



Application::Application(const char* name, unsigned int screenWidth, unsigned int screenHeight)
{
	this->name = name;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	/* Initialize the library */
	if (!glfwInit()) return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, name, NULL, NULL);
	if (!window) glfwTerminate();

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "[ERROR] GLEW not initialized properly!" << std::endl;
		return;
	}

	glfwSetKeyCallback(window, keyCallback);
 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
}

Application::Application()
{
}


Application::~Application()
{
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

void Application::mouseCallback(GLFWwindow * window, double xPos, double yPos)
{
	mouseX = xPos;
	mouseY = yPos;
}

unsigned int Application::getScreenWidth()
{
	return screenWidth;
}

unsigned int Application::getScreenHeight()
{
	return screenHeight;
}

double Application::getMouseX()
{
	return mouseX;
}

double Application::getMouseY()
{
	return mouseY;
}
