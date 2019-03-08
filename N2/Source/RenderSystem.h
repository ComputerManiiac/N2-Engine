#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "System.h"
#include "RenderComponent.h"
#include "MatrixStack.h"
#include <vector>

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();

	void Initialize();
	void Update(double dt);

	void registerComp(Component* component);
	void removeComp(Component* component);


private:
	unsigned int VAO;
	std::vector<RenderComponent*> subscribers;
	MS modelStack, projectionStack, viewStack;

};

#endif