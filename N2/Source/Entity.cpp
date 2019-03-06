#include "Entity.h"
#include "Loader.h"


Entity::Entity()
{
	addComponent(new TransformComponent(this));
	addComponent(new RenderComponent(this, OBJInfo::generateCube(), Loader::loadTGA("Assets\\Textures\\rock.tga")));
	
}


Entity::~Entity()
{
}
