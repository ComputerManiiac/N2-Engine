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

std::vector<Vector3> ColliderComponent::getVertices() const
{
	return getVertices(Vector3(0, 0, 0), Vector3(0, 0, 0));
}

std::vector<Vector3> ColliderComponent::getVertices(const Vector3& trans, const Vector3& rot) const
{
	TransformComponent* transform = parent->getComponent<TransformComponent>();
	const Vector3& translation = transform->getPos();
	const Vector3& rotation = transform->getRot();
	const Vector3& scale = transform->getScale();

	std::vector<Vector3> transformVertices;
	for (Vector3 vertex : vertices)
	{
		vertex += translation + trans;
		vertex.x *= scale.x;
		vertex.y *= scale.y;
		vertex.z *= scale.z;
		transformVertices.push_back(vertex.Rotate(rotation).Rotate(rot));
	}

	return transformVertices;
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
