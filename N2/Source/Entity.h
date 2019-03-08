#ifndef ENTITY_H
#define ENTITY_H

#include "OverloadNew.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include <map>
#include <typeinfo>
#include <typeindex>

class Entity
{
public:
	Entity();
	virtual ~Entity();


	template<typename T>
	void addComponent(T* component);

	template<typename T>
	T* getComponent();

private:
	std::map<std::type_index, Component*> components;
};


template<typename T>
void Entity::addComponent(T* component)
{
	std::type_index id = std::type_index(typeid(component));
	if (components.find(id) != components.end())
		delete components[id];
	components[id] = component;
}

template<typename T>
T* Entity::getComponent()
{

	std::type_index id = std::type_index(typeid(T*));
	if (components.find(id) != components.end())
	{
		Component* comp = components[id];
		T* tComp = dynamic_cast<T*>(comp);
		if (tComp == nullptr)
			std::cout << "[ERROR] Trying to retrieve component of type " << typeid(T).name() << " from Entity which does not exist!" << std::endl;

		return tComp;
	}
	else
	{
		std::cout << "[ERROR] Trying to retrieve component of type " << typeid(T).name() << " from Entity which does not exist!" << std::endl;
		return nullptr;
	}
}

#endif