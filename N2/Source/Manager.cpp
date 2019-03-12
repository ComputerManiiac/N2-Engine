#include "Manager.h"

Manager* Manager::instance = nullptr;



Manager::Manager()
{
	
}


Manager * Manager::getInstance()
{
	if (instance == nullptr)
		instance = new Manager();
	return instance;
}

Manager::~Manager()
{

	for (auto& system : systems)
	{
		delete system.second;
	}

	for (auto& entity : entities) {
		delete entity.second;
	}

	for (auto& shader : shaders){
		delete shader.second;
	}

}

void Manager::Initialize()
{

	camera = Camera(Vector3(0, 1, 5));
	shaders["lit"] = new ShaderProgram("Assets\\Shaders\\lit.vert", "Assets\\Shaders\\lit.frag");
	
	registerSystem<RenderSystem>();
	registerSystem<PhysicsSystem>();
	
	entities["abc"] = new Entity(Vector3(0, 5, 0));
	entities["ground"] = new Entity(Vector3(0, 0, 0), Vector3(0,0,0), Vector3(100,1,100), OBJInfo::genCube(), Loader::loadTGA("Assets\\Textures\\human.tga"));
	entities["test"] = new Entity(Vector3(8,5,0), Vector3(0,30,0), Vector3(1, 1, 1), Loader::loadOBJ("Assets\\Models\\devastator.obj"), 
		Loader::loadTGA("Assets\\Textures\\devastator.tga"));

	

	for (auto& system : systems) {
		system.second->Initialize();
	}





}

Camera * Manager::getCamera()
{
	return &camera;
}

ShaderProgram * Manager::getShader(const std::string & name)
{
	return shaders[name];
}


void Manager::Update(double dt)
{

	for (auto& system : systems)
	{
		System* sys = system.second;
		sys->Update(dt);
	}
	camera.Update(dt);

}