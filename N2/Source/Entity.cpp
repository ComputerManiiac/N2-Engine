#include "Entity.h"
#include "Loader.h"
#include "Manager.h"


Entity::Entity()
{
	addComponent(new TransformComponent(this));
	RenderComponent* render = new RenderComponent(this, OBJInfo::generateCube(), Loader::loadTGA("Assets\\Textures\\rock.tga"));
	addComponent(render);
	Manager::getInstance()->registerComponent<RenderSystem>(render);
}


Entity::~Entity()
{
}
