#ifndef MANAGER_H
#define MANAGER_H

#include "Core.h"
#include "Camera.h"
#include <typeindex>
#include <vector>

class Manager
{
public:
	static Manager* getInstance();
	~Manager();
	
	void Initialize();
	void Update(double dt);

	template<typename T>
	void registerComponent(Component* component);

	template<typename T>
	void registerSystem();

	template<typename T>
	T* getSystem();

	Camera* getCamera();
	ShaderProgram* getShader(const std::string& name);

private:

	Manager();
	static Manager* instance;
	std::map<std::type_index, System*> systems;
	std::map<std::string, ShaderProgram*> shaders;
	std::map<std::string, Entity*> entities;
	Camera camera;
	Entity* entity;
};


template<typename T>
void Manager::registerComponent(Component * component)
{
	systems[std::type_index(typeid(T*))]->registerComp(component);
}


template<typename T>
void Manager::registerSystem() {
	systems[std::type_index(typeid(T*))] = new T();
}


template<typename T>
T* Manager::getSystem()
{
	return dynamic_cast<T*>(systems[std::type_index(typeid(T*))]);
}

#endif