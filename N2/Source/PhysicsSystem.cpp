#include "PhysicsSystem.h"
#include "Entity.h"


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
	Vector3 grav = Vector3(0, -9.8, 0) * dt;
	for (ColliderComponent* sub : subscribers)
	{
		if (sub->getParent()->getName() == "ground") continue;

		std::vector<ColliderComponent*> nearby;
		getNearbyColliders(sub, nearby);

		bool onGround = false;
		for (ColliderComponent* collider : nearby)
		{
			if (checkCollision(sub, collider, grav, Vector3(0, 0, 0)))
			{
				onGround = true;
				break;
			}
		}
		if (!onGround)
		{
			sub->getParent()->getComponent<TransformComponent>()->Move(grav);
			std::cout << "Moving Down |" << std::endl;
		}

	}




}



bool PhysicsSystem::checkCollision(ColliderComponent* collider, ColliderComponent* other, const Vector3& translation, const Vector3& rotation)
{
	Vector3 mtv;
	return checkCollision(collider, other, translation, rotation, mtv);
}

bool PhysicsSystem::checkCollision(ColliderComponent* collider, ColliderComponent* other, const Vector3& translation, const Vector3& rotation, Vector3& mtv)
{
	TransformComponent* t1 = collider->getParent()->getComponent<TransformComponent>();
	TransformComponent* t2 = other->getParent()->getComponent<TransformComponent>();

	std::vector<Vector3> axes;
	generateAxes(t1, t2, axes);

	bool hasCalculated = false;
	float minOverlap = 0.0f;

	for (const Vector3& axis : axes)
	{

		float minA, maxA, minB, maxB;
		getProjOverlap(collider, translation, rotation, axis, minA, maxA);
		getProjOverlap(other, Vector3(0,0,0), Vector3(0,0,0), axis, minB, maxB);

		float overlap = getLineOverlap(minA, maxA, minB, maxB);

		if (overlap == 0)
		{
			return false;
		}

		if (!hasCalculated || overlap < minOverlap)
		{
			hasCalculated = true;
			minOverlap = overlap;
			mtv = axis;
		}
	}
	

	Vector3 dir = t2->getPos() - t1->getPos();
	if (mtv.Dot(dir) >= 0)
		mtv = -mtv;

	mtv *= minOverlap;

	return true;
}



void PhysicsSystem::getNearbyColliders(ColliderComponent* self, std::vector<ColliderComponent*>& nearby)
{
	for (ColliderComponent* sub : subscribers)
	{
		if (sub != self)
			nearby.push_back(sub);
	}
}

void PhysicsSystem::getProjOverlap(ColliderComponent* collider, const Vector3& translation, const Vector3& rotation, const Vector3& axis, float& min, float& max)
{
	const std::vector<Vector3>& vertices = collider->getVertices(translation, rotation);
	min = vertices[0].Dot(axis);
	max = min;

	for (int i = 1; i < (int) vertices.size(); i++)
	{
		float dist = vertices[i].Dot(axis);
		if (dist < min) min = dist;
		if (dist > max) max = dist;
	}

}

void PhysicsSystem::generateAxes(TransformComponent* transform, TransformComponent* other, std::vector<Vector3>& axes)
{
	Vector3 localAxes[6];
	transform->getLocalAxes(localAxes);
	other->getLocalAxes(localAxes + 3);

	for (const Vector3& axis : localAxes)
		axes.push_back(axis);
	
	// Take into consideration the edges of each object, by crossing each local axis of one with another.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			Vector3 result = localAxes[i].Cross(localAxes[j]);
			if(result != Vector3(0,0,0))
				axes.push_back(result);
		}
	}
}

float PhysicsSystem::getLineOverlap(float & aMin, float & aMax, float & bMin, float & bMax)
{
	return Math::Max(0.0f, Math::Min(aMax, bMax) - Math::Max(aMin, bMin));
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
