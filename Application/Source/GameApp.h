#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "Application.h"

class GameApp : public Application
{
public:
	GameApp(const char* name, unsigned int screenWidth, unsigned int screenHeight);
	GameApp();
	~GameApp();

	void Initialize();
	void Run();
	void Deinitialize();
};

#endif