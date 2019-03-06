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
		System* sys = system.second;
		sys->Deinitialize();
	}

	for (auto& system : systems) {
		delete system.second;
	}

	for (auto& shader : shaders){
		delete shader.second;
	}

}

void Manager::Initialize()
{

	camera = Camera(Vector3(0, 0, 0));


	shaders["lit"] = new ShaderProgram("Assets\\Shaders\\lit.vert", "Assets\\Shaders\\lit.frag");

	registerSystem<RenderSystem>();

	entity = new Entity();

	for (auto& system : systems)
	{
		System* sys = system.second;
		sys->Initialize();
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


void Manager::Update()
{
	for (auto& system : systems)
	{
		System* sys = system.second;
		sys->Update();
	}
}