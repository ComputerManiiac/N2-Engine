#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <iostream>
#include "Component.h"
#include "Vector3.h"

class TransformComponent : public Component
{
public:

	TransformComponent(Entity* parent, Vector3 pos, Vector3 rot, Vector3 scale);
	TransformComponent(Entity* parent);
	TransformComponent();
	~TransformComponent();

	void setPos(const Vector3& pos);
	void setScale(const Vector3& scale);
	void setRot(const Vector3& rot);

	const Vector3& getPos() const;
	const Vector3& getRot() const;
	const Vector3& getScale() const;
	

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

#endif