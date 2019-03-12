#include "Entity.h"
#include "Loader.h"
#include "Manager.h"


Entity::Entity(Vector3 position, Vector3 rotation, Vector3 scale, OBJInfo model, unsigned int texture)
{
	addComponent(new TransformComponent(this, position, rotation, scale));
	addComponent(new RenderComponent(this, model, texture));

	Manager::getInstance()->registerComponent<RenderSystem>(getComponent<RenderComponent>());
	addComponent(new ColliderComponent(this));
	Manager::getInstance()->registerComponent<PhysicsSystem>(getComponent<ColliderComponent>());
}

Entity::Entity(Vector3 position)
{
	addComponent(new TransformComponent(this, position, Vector3(0,0,0), Vector3(1,1,1)));
	addComponent(new RenderComponent(this, Loader::loadOBJ("Assets\\Models\\Toolbox.obj"),
		Loader::loadTGA("Assets\\Textures\\Smite.tga")));
	addComponent(new ColliderComponent(this));

	Manager::getInstance()->registerComponent<RenderSystem>(getComponent<RenderComponent>());
	Manager::getInstance()->registerComponent<PhysicsSystem>(getComponent<ColliderComponent>());

}

Entity::Entity(OBJInfo model)
{

}

Entity::Entity()
{
	
}


Entity::~Entity()
{
	for (auto& component : components) {
		delete component.second;
	}
}


