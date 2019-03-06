#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "Application.h"
#include "Core.h"


class GameApp : public Application
{
public:
	GameApp(const char* name, unsigned int screenWidth, unsigned int screenHeight);
	GameApp();
	~GameApp();

	void Run();
};

#endif