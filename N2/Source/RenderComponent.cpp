#include "RenderComponent.h"


RenderComponent::RenderComponent(Entity* parent, OBJInfo info, unsigned int textureID, DRAW_MODE mode) : Component("Render", parent)
{

	this->mode = mode;
	this->info = info;
	this->textureID = textureID;

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

void RenderComponent::setBufferObjects(const unsigned int & VBO, const unsigned int & IBO)
{
	this->VBO = VBO;
	this->IBO = IBO;
}


OBJInfo RenderComponent::getInfo()
{
	return info;
}

DRAW_MODE RenderComponent::getMode()
{
	return mode;
}

unsigned int RenderComponent::getVBO()
{
	return VBO;
}

unsigned int RenderComponent::getIBO()
{
	return IBO;
}

unsigned int RenderComponent::getTexID()
{
	return textureID;
}

