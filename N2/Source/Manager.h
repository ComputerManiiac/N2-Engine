#ifndef MANAGER_H
#define MANAGER_H

#include "OverloadNew.h"
#include "System.h"
#include "RenderSystem.h"

#include <typeindex>
#include <vector>

class Manager
{
public:
	static Manager* getInstance();
	~Manager();

	template<typename T>
	void registerComponent(Component* component);

private:
	Manager();
	static Manager* instance;
	std::map<std::type_index, System*> systems;

};

template<typename T>
void Manager::registerComponent(Component * component)
{
	systems[std::type_index(typeid(T*))]->registerComp(component);
}

#endif