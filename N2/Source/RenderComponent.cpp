#include "RenderComponent.h"


RenderComponent::RenderComponent(Entity* parent, OBJInfo info, unsigned int textureID, DRAW_MODE mode) : Component("Render", parent)
{

	this->mode = mode;
	this->info = info;
	this->textureID = textureID;

	material = Material(Vector3(0.2f, 0.2f, 0.2f), Vector3(0.1f,0.1f,0.1f), 1.0f);
}


RenderComponent::RenderComponent(Entity* parent) : Component("Render", parent)
{
	
}

RenderComponent::RenderComponent()
{
}


RenderComponent::~RenderComponent()
{

}

void RenderComponent::setBufferObjects(const unsigned int & VBO, const unsigned int & EBO)
{
	this->VBO = VBO;
	this->EBO = EBO;
}


const OBJInfo& RenderComponent::getInfo() const
{
	return info;
}

const DRAW_MODE& RenderComponent::getMode() const
{
	return mode;
}

const Material& RenderComponent::getMaterial() const
{
	return material;
}

const unsigned int& RenderComponent::getVBO() const
{
	return VBO;
}

const unsigned int& RenderComponent::getEBO() const
{
	return EBO;
}

const unsigned int& RenderComponent::getTexID() const
{
	return textureID;
}

