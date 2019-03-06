#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <map>

class Application
{
public:
	
	Application(const char* name, unsigned int screenWidth, unsigned int screenHeight);
	Application();
	virtual ~Application();

	virtual void Run();

	static bool isKeyPressed(int key);
	static bool isKeyPressDown(int key);
	static bool isKeyPressRelease(int key);

	static unsigned int getScreenWidth();
	static unsigned int getScreenHeight();

	static double getMouseX();
	static double getMouseY();

private:

	static void keyCallback(GLFWwindow* window, int key, int scanNode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xPos, double yPos);

protected:

	static std::map<int, bool> keyDown;
	static std::map<int, bool> keyRelease;

	static double mouseX;
	static double mouseY;
	static unsigned int screenWidth;
	static unsigned int screenHeight;
	static GLFWwindow* window;

	const char* name;

};

#endif