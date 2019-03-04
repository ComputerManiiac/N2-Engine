#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
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
	components[std::type_index(typeid(component))] = component;
}

template<typename T>
T* Entity::getComponent()
{
	Component* comp = components[std::type_index(typeid(T*))];
	return dynamic_cast<T*>(comp);
}

#endif