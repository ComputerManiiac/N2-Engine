#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <vector>
#include "System.h"
#include "ColliderComponent.h"

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Initialize();
	void Update(double dt);

	void registerComp(Component* component);
	void removeComp(Component* component);

private:
	std::vector<ColliderComponent*> subscribers;
};

#endif