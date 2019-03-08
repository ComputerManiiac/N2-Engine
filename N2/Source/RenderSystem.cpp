#include "RenderSystem.h"
#include "Application.h"
#include "Manager.h"

RenderSystem::RenderSystem()
{

}



RenderSystem::~RenderSystem()
{
	glDeleteVertexArrays(1, &VAO);
}

void RenderSystem::Initialize() {
	Mtx44 proj;
	proj.SetToPerspective(45.0f, (float)Application::getScreenWidth() / (float)Application::getScreenHeight(), 0.1f, 10000.0f);
	projectionStack.LoadMatrix(proj);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	for (auto& sub : subscribers)
	{
		unsigned int VBO, EBO;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		const OBJInfo& info = sub->getInfo();

		

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, info.getVertices().size() * sizeof(Vertex), &info.getVertices().at(0), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.getIndices().size() * sizeof(unsigned int), &info.getIndices().at(0), GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) sizeof(Vector3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));
		glEnableVertexAttribArray(2);






		sub->setBufferObjects(VBO, EBO);
		std::cout << "Initialized: " << this << std::endl;
	}
	glBindVertexArray(0);
}


void RenderSystem::Update(double dt)
{
	modelStack.LoadIdentity();
	viewStack.LoadMatrix(Manager::getInstance()->getCamera()->LookAt());


	glBindVertexArray(VAO);
	glEnable(GL_TEXTURE_2D);
	for (auto& sub : subscribers)
	{
		modelStack.PushMatrix();

		TransformComponent* transform = sub->getParent()->getComponent<TransformComponent>();
		const Vector3& position = transform->getPos();
		modelStack.Translate(position.x, position.y, position.z);
		

		Mtx44 MVP, modelView, modelView_inverse_tranpose;
		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		modelView = viewStack.Top() * modelStack.Top();

		const Material& mat = sub->getMaterial();
		const Vector3& diffuse = mat.getDiffuse();
		const Vector3& specular = mat.getSpecular();
		const DRAW_MODE& mode = sub->getMode();
		const unsigned int& indexSize = sub->getInfo().getIndices().size();
		const unsigned int& textureID = sub->getTexID();
		const unsigned int& vertexBuffer = sub->getVBO();

		ShaderProgram* lit = Manager::getInstance()->getShader("lit");
		lit->Use();
		lit->setMat4("MVP", MVP);
		lit->setMat4("MV", modelView);
		lit->setMat4("model", modelStack.Top());

		lit->setVec3("material.kDiffuse", diffuse.x, diffuse.y, diffuse.z);
		lit->setVec3("material.kSpecular", specular.x, specular.y, specular.z);
		lit->setVec3("material.kShininess", mat.getShininess());

		lit->setInt("colorTextureEnabled", 1);
		lit->setInt("colorTexture", 0);

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

	}
	glDisable(GL_TEXTURE_2D);
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