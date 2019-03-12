#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Initialize()
{
}

void PhysicsSystem::Update(double dt)
{
}

void PhysicsSystem::registerComp(Component* component)
{
	ColliderComponent* collider = dynamic_cast<ColliderComponent*>(component);
	if (collider != nullptr)
		subscribers.push_back(collider);
}

void PhysicsSystem::removeComp(Component* component)
{
}
