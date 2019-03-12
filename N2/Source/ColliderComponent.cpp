#include "ColliderComponent.h"
#include "Entity.h"




ColliderComponent::ColliderComponent(Entity* parent) : Component("Collider", parent)
{
	/*this->scale = parent->getComponent<RenderComponent>()->getInfo().getColliderScale();*/
	vertices = OBJInfo::genBoxCollider(parent->getComponent<RenderComponent>()->getInfo());
	scale = vertices[1] - vertices[0];
	drawCollider = true;
}

ColliderComponent::ColliderComponent()
{
}


ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::setBufferObjects(const unsigned int& VAO, const unsigned int& VBO, const unsigned int& EBO)
{
	this->VAO = VAO;
	this->VBO = VBO;
	this->EBO = EBO;
}

const Vector3 & ColliderComponent::getScale() const
{
	return scale;
}

const std::vector<Vector3>& ColliderComponent::getVertices() const
{
	return vertices;
}

const bool& ColliderComponent::shouldDrawCollider() const
{
	return drawCollider;
}

const unsigned int& ColliderComponent::getVAO() const
{
	return VAO;
}

const unsigned int& ColliderComponent::getVBO() const
{
	return VBO;
}

const unsigned int& ColliderComponent::getEBO() const
{
	return EBO;
}
