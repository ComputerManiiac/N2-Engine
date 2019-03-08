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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.getIndices()->size() * sizeof(unsigned int), &info.getIndices()->at(0), GL_STATIC_DRAW);


		//glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		//glEnableVertexAttribArray(0);

		//glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) sizeof(Vector3));
		//glEnableVertexAttribArray(1);

		//glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));
		//glEnableVertexAttribArray(2);






		sub->setBufferObjects(VBO, EBO);
		std::cout << "Initialized: " << this << std::endl;
	}

	//glBindVertexArray(0);
}


void RenderSystem::Update(double dt)
{
	
	viewStack.LoadMatrix(Manager::getInstance()->getCamera()->LookAt());
	modelStack.LoadIdentity();
	//glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);
	for (auto& sub : subscribers)
	{
		modelStack.PushMatrix();

		//TransformComponent* transform = sub->getParent()->getComponent<TransformComponent>();
		//Vector3 position = transform->getPos();
		//modelStack.Translate(position.x, position.y, position.z);
		

		Mtx44 MVP, modelView, modelView_inverse_tranpose;
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		modelView = viewStack.Top() * modelStack.Top();

		ShaderProgram* lit = Manager::getInstance()->getShader("lit");
		lit->Use();
		lit->setMat4("MVP", MVP);
		lit->setMat4("MV", modelView);
		lit->setMat4("model", modelStack.Top());
		lit->setInt("colorTextureEnabled", 1);
		lit->setInt("colorTexture", 0);
		

		DRAW_MODE mode = sub->getMode();
		unsigned int indexSize = sub->getInfo().getIndices()->size();
		unsigned int textureID = sub->getTexID();
		unsigned int vertexBuffer = sub->getVBO();
		unsigned int indexBuffer = sub->getEBO();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glDrawElements(GL_TRIANGLES, sub->getInfo().getIndices()->size(), GL_UNSIGNED_INT, 0);


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) sizeof(Vector3));
		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		if (mode == DRAW_TRIANGLE_STRIP)
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_LINES)
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
		else if (mode == DRAW_FAN)
			glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
		else
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		if (textureID > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(3);
		}

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);


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