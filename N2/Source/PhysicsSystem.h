#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <vector>
#include "System.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Initialize();
	void Update(double dt);

	void registerComp(Component* component);
	void removeComp(Component* component);

	/* Intersection */
	bool checkCollision(ColliderComponent* collider, ColliderComponent* other, const Vector3& translation, const Vector3& rotation);
	bool checkCollision(ColliderComponent* collider, ColliderComponent* other, const Vector3& translation, const Vector3& rotation, Vector3& mtv);


private:


	void getNearbyColliders(ColliderComponent* self, std::vector<ColliderComponent*>& nearby);

	/* Separating Axis Theorem */
	void getProjOverlap(ColliderComponent* collider, const Vector3& translaation, const Vector3& rotation, const Vector3& axis, float& min, float& max);
	float getLineOverlap(float& aMin, float& aMax, float& bMin, float& bMax);
	void generateAxes(TransformComponent* collider, TransformComponent* other, std::vector<Vector3>& axes);

	std::vector<ColliderComponent*> subscribers;
};

#endif