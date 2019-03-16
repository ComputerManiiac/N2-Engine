#include "Manager.h"
#include "Application.h"

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
	
	entities["car"] = new Entity("car", Vector3(0, 10, 0), Vector3(0, 45, 0), Vector3(1, 1, 1), Loader::loadOBJ("Assets\\Models\\devastator.obj"), Loader::loadTGA("Assets\\Textures\\rock.tga"));
	entities["another"] = new Entity("car2", Vector3(1, 100, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), Loader::loadOBJ("Assets\\Models\\devastator.obj"), Loader::loadTGA("Assets\\Textures\\devastator.tga"));
	//entities["test"] = new Entity(Vector3(1, 5, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), Loader::loadOBJ("Assets\\Models\\devastator.obj"),
	//	Loader::loadTGA("Assets\\Textures\\devastator.tga"));
	entities["ground"] = new Entity("ground", Vector3(0, 0, 0), Vector3(0,0,0), Vector3(100,1,100), OBJInfo::genCube(), Loader::loadTGA("Assets\\Textures\\human.tga"));


	

	for (auto& system : systems) {
		system.second->Initialize();
	}





}

Camera* Manager::getCamera()
{
	return &camera;
}

ShaderProgram * Manager::getShader(const std::string & name)
{
	return shaders[name];
}


void Manager::Update(double dt)
{

	if (Application::isKeyPressDown(GLFW_KEY_L))
	{
		Vector3 mtv;
		//
		//std::cout << (getSystem<PhysicsSystem>()->checkCollision(entities["abc"]->getComponent<ColliderComponent>(), 
		//	entities["another"]->getComponent<ColliderComponent>(), mtv) ? "True" : "False") << std::endl;

		while(getSystem<PhysicsSystem>()->checkCollision(entities["car"]->getComponent<ColliderComponent>(),
			entities["ground"]->getComponent<ColliderComponent>(), Vector3(0,0,0), Vector3(0,0,0), mtv))
		{
			std::cout << mtv << std::endl;
			std::cout << "True" << std::endl;
			entities["abc"]->getComponent<TransformComponent>()->Move(mtv);
		}
	}

	for (auto& system : systems)
	{
		System* sys = system.second;
		sys->Update(dt);
	}
	camera.Update(dt);

}