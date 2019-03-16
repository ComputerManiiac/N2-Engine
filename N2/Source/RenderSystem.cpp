#include "RenderSystem.h"
#include "Application.h"
#include "Manager.h"

RenderSystem::RenderSystem()
{

}



RenderSystem::~RenderSystem()
{
	for (auto& sub : subscribers)
	{
		const unsigned int& VAO = sub->getVAO();
		const unsigned int& VBO = sub->getVBO();
		const unsigned int& EBO = sub->getEBO();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


	for (LightSource* light : lightSources)
	{
		delete light;
	}
}

void RenderSystem::Initialize() {

	// Defines projection matrix for the scene
	Mtx44 proj;
	proj.SetToPerspective(45.0f, (float)Application::getScreenWidth() / (float)Application::getScreenHeight(), 0.1f, 10000.0f);
	projectionStack.LoadMatrix(proj);

	// Generates vertex arrays and buffers for each render component and populates the assigned int into them
	for (RenderComponent* sub : subscribers)
	{
		unsigned int VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		initializeOBJ(sub->getInfo(), VAO, VBO, EBO);
		sub->setBufferObjects(VAO, VBO, EBO);

		ColliderComponent* collider = sub->getParent()->getComponent<ColliderComponent>();
		if (collider != nullptr)
		{
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			initializeOBJ(OBJInfo::genCube(), VAO, VBO, EBO);
			collider->setBufferObjects(VAO, VBO, EBO);
		}
	}

	setupLight();
}

// Sets up how attributes are layed out in the VAO before buffering data into VBO
void RenderSystem::initializeOBJ(const OBJInfo& info, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, info.getVertices().size() * sizeof(Vertex), &info.getVertices().at(0), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.getIndices().size() * sizeof(unsigned int), &info.getIndices().at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));
}

// Sets up values for all the lights in the Scene
void RenderSystem::setupLight()
{
	LightSource* light = new LightSource(LIGHT_POINT);
	light->setPointLight(Vector3(0, 5, 0), Vector3(0, 0, 1), 1.0f, 1.0f, 0.01f, 0.001f);
	light->setupAttribs(Manager::getInstance()->getShader("lit"));
	lightSources.push_back(light);


	LightSource* light2 = new LightSource(LIGHT_POINT);
	light2->setPointLight(Vector3(5, 5, 0), Vector3(1, 0, 0), 1.0f, 1.0f, 0.01f, 0.001f);
	light2->setupAttribs(Manager::getInstance()->getShader("lit"));
	lightSources.push_back(light2);

	LightSource* light3 = new LightSource(LIGHT_SPOTLIGHT);
	light3->setSpotLight(Vector3(0, 4, 0), Vector3(1, 1, 1), Vector3(0, -1, 0), 1.0f, 45.0f, 30.0f, 1.0f, 1.0f, 0.01f, 0.001f);
	light3->setupAttribs(Manager::getInstance()->getShader("lit"));
	lightSources.push_back(light3);

	Manager::getInstance()->getShader("lit")->Use();
	Manager::getInstance()->getShader("lit")->setInt("numLights", LightSource::getCount());
}


// Uses data that are stored in the RenderComponent (stored previously through Initialize) to draw objects
void RenderSystem::Update(double dt)
{
	modelStack.LoadIdentity();
	viewStack.LoadMatrix(Manager::getInstance()->getCamera()->LookAt());

	for (LightSource* light : lightSources)
	{
		light->updateAttribs(Manager::getInstance()->getShader("lit"), viewStack);
	}

	glEnable(GL_TEXTURE_2D);
	for (auto& sub : subscribers)
	{
		if (!sub->isActive()) continue;

		glBindVertexArray(sub->getVAO());
		modelStack.PushMatrix();

		TransformComponent* transform = sub->getParent()->getComponent<TransformComponent>();
		updateTransform(transform);
		updateShader(sub);

		const unsigned int& indexSize = sub->getInfo().getIndices().size();
		const unsigned int& textureID = sub->getTexID();
		const DRAW_MODE& mode = sub->getMode();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		if (mode == DRAW_TRIANGLE_STRIP)
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_LINES)
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_FAN)
			glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
		else
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		modelStack.PopMatrix();

		ColliderComponent* collider = sub->getParent()->getComponent<ColliderComponent>();
		if (collider != nullptr && collider->shouldDrawCollider())
			drawCollider(collider);

		glBindVertexArray(0);

	}
	glDisable(GL_TEXTURE_2D);
}

// Apply an object's transformations to the model stack
void RenderSystem::updateTransform(TransformComponent* transform)
{
	const Vector3& position = transform->getPos();
	const Vector3& rotation = transform->getRot();
	const Vector3& scale = transform->getScale();
	modelStack.Translate(position);
	modelStack.Rotate(rotation);
	modelStack.Scale(scale);
}

// Update an object's transformational related information, as well as material and texture for lighting.
void RenderSystem::updateShader(RenderComponent* render)
{
	Mtx44 MVP, modelView, modelView_inverse_tranpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	modelView = viewStack.Top() * modelStack.Top();
	modelView_inverse_tranpose = modelView.GetInverse().GetTranspose();

	const Material& mat = render->getMaterial();
	const Vector3& ambient = mat.getAmbient();
	const Vector3& diffuse = mat.getDiffuse();
	const Vector3& specular = mat.getSpecular();

	ShaderProgram* lit = Manager::getInstance()->getShader("lit");
	lit->Use();
	lit->setMat4("MVP", MVP);
	lit->setMat4("MV", modelView);
	lit->setMat4("MV_inverse_transpose", modelView_inverse_tranpose);
	lit->setMat4("view", viewStack.Top());

	lit->setVec3("material.kAmbient", ambient.x, ambient.y, ambient.z);
	lit->setVec3("material.kDiffuse", diffuse.x, diffuse.y, diffuse.z);
	lit->setVec3("material.kSpecular", specular.x, specular.y, specular.z);
	lit->setFloat("material.kShininess", mat.getShininess());

	lit->setInt("colorTextureEnabled", 1);
	lit->setInt("colorTexture", 0);
}


// Draws an object's box collider
void RenderSystem::drawCollider(ColliderComponent* collider)
{

	const OBJInfo& cube = OBJInfo::genCube();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(collider->getVAO());
	modelStack.PushMatrix();

	updateTransform(collider->getParent()->getComponent<TransformComponent>());
	modelStack.Scale(collider->getScale());
	updateShader(collider->getParent()->getComponent<RenderComponent>());

	ShaderProgram* lit = Manager::getInstance()->getShader("lit");
	lit->setInt("colorTextureEnabled", 0);
	lit->setBool("lightEnabled", false);

	const unsigned int& indexSize = cube.getIndices().size();
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	lit->setBool("lightEnabled", true);
	modelStack.PopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
}



void RenderSystem::registerComp(Component* component)
{
	RenderComponent* render = dynamic_cast<RenderComponent*>(component);
	if (render != nullptr)
		subscribers.push_back(render);
}

void RenderSystem::removeComp(Component* component)
{
	RenderComponent* render = dynamic_cast<RenderComponent*>(component);
	if (render != nullptr)
		subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), render));
}