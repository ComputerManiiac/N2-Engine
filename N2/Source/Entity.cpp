#include "Entity.h"
#include "Loader.h"
#include "Manager.h"


Entity::Entity()
{
	addComponent(new TransformComponent(this));

	RenderComponent* render = new RenderComponent(this, Loader::loadOBJ("Assets\\Models\\Smite.obj"),
		Loader::loadTGA("Assets\\Textures\\Smite.tga"));
	addComponent(render);

	Manager::getInstance()->registerComponent<RenderSystem>(render);
}


Entity::~Entity()
{
	for (auto& component : components) {
		delete component.second;
	}
}


