#include "RenderSystem.h"
#include "Application.h"
#include "Manager.h"

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}


void RenderSystem::Initialize()
{
	Mtx44 proj;
	proj.SetToPerspective(45.0f, (float) Application::getScreenWidth() / (float)Application::getScreenHeight(), 0.1f, 10000.0f);
	projectionStack.LoadMatrix(proj);
	

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	for (auto& sub : subscribers)
	{
		unsigned int VBO, EBO;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		OBJInfo& info = sub->getInfo();
		

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, info.getVertices()->size() * sizeof(Vertex), &info.getVertices()->at(0), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) sizeof(Vector3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.getIndices()->size() * sizeof(unsigned int), &info.getIndices()->at(0), GL_STATIC_DRAW);
		




		sub->setBufferObjects(VBO, EBO);
		std::cout << "Initialized: " << this << std::endl;
	}

	glBindVertexArray(0);
}


void RenderSystem::Update()
{
	
	viewStack.LoadMatrix(Manager::getInstance()->getCamera()->LookAt());
	modelStack.LoadIdentity();

	for (auto& sub : subscribers)
	{
		modelStack.PushMatrix();

		TransformComponent* transform = sub->getParent()->getComponent<TransformComponent>();
		Vector3 position = transform->getPos();
		modelStack.Translate(position.x, position.y, position.z);
		

		Mtx44 MVP, modelView, modelView_inverse_tranpose;
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		modelView = viewStack.Top() * modelStack.Top();

		Manager::getInstance()->getShader("lit")->Use();

		glBindVertexArray(VAO);
		DRAW_MODE mode = sub->getMode();
		unsigned int indexSize = sub->getInfo().getIndices()->size();

		glBindTexture(GL_TEXTURE_2D, sub->getTexID());

		if (mode == DRAW_TRIANGLE_STRIP)
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_LINES)
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_FAN)
			glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
		else
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		modelStack.PopMatrix();

	}
}

void RenderSystem::Deinitialize()
{
	glDeleteVertexArrays(1, &VAO);
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