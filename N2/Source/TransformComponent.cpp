#include "TransformComponent.h"

TransformComponent::TransformComponent(Entity* parent, Vector3 pos, Vector3 rot, Vector3 scale) : Component("Transform", parent)
{
	this->position = pos;
	this->rotation = rot;
	this->scale = scale;
}


TransformComponent::TransformComponent(Entity* parent) : Component("Transform", parent)
{
	/*position.SetZero();*/
	position.Set(0,0,0);
	rotation.SetZero();
	scale.Set(1, 1, 1);
}

TransformComponent::TransformComponent()
{
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::Move(const Vector3& delta)
{
	position += delta;
}

void TransformComponent::setPos(const Vector3& pos)
{
	this->position = pos;
}

void TransformComponent::setRot(const Vector3& rot)
{
	this->rotation = rot;
}

void TransformComponent::setScale(const Vector3 & scale)
{
	this->scale = scale;
}

const Vector3& TransformComponent::getPos() const
{
	return position;
}

const Vector3& TransformComponent::getRot() const
{
	return rotation;
}	

const Vector3& TransformComponent::getScale() const
{
	return scale;
}

void TransformComponent::getLocalAxes(Vector3* axes) const
{
	// X Axis
	*axes = Vector3(1, 0, 0).Rotate(Vector3(0, rotation.y, 0)).Rotate(Vector3(0, 0, rotation.z));
	// Y Axis
	*(axes+1) = Vector3(0, 1, 0).Rotate(Vector3(rotation.x, 0, 0)).Rotate(Vector3(0, 0, rotation.z));
	// Z Axis
	*(axes+2) = Vector3(0, 0, 1).Rotate(Vector3(0, rotation.y, 0)).Rotate(Vector3(rotation.x, 0, 0));
}



