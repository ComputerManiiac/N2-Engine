#include "Manager.h"

Manager* Manager::instance = nullptr;

Manager::Manager()
{
	registerSystem<RenderSys>();
}


Manager * Manager::getInstance()
{
	if (instance == nullptr)
		instance = new Manager();
	return instance;
}

Manager::~Manager()
{

	for (auto& system : systems) {
		delete system.second;
	}

}


