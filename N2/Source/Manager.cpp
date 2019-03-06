#include "Manager.h"

Manager* Manager::instance = nullptr;

Manager::Manager()
{
	RenderSystem<RenderComponent>* system = new RenderSystem<RenderComponent>();
	systems[std::type_index(typeid(system))] = system;
}


Manager * Manager::getInstance()
{
	if (instance == nullptr)
		instance = new Manager();
	return instance;
}

Manager::~Manager()
{
}


