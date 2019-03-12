#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "System.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"
#include "MatrixStack.h"
#include "LightSource.h"
#include <vector>

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();

	void Initialize();
	void initializeOBJ(const OBJInfo& info, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void setupLight();

	void Update(double dt);
	void updateShader(RenderComponent* renderComp);
	void drawCollider(ColliderComponent* colliderComp);
	


	void registerComp(Component* component);
	void removeComp(Component* component);


private:
	std::vector<RenderComponent*> subscribers;
	std::vector<LightSource*> lightSources;
	MS modelStack, projectionStack, viewStack;

};

#endif