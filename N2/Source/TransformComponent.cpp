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

void TransformComponent::setPos(const Vector3 & pos)
{
	this->position = pos;
}

void TransformComponent::setRot(const Vector3 & rot)
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
