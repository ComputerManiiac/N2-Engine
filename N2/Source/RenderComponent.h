#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <GL\glew.h>
#include "Component.h"
#include "OBJInfo.h"

enum DRAW_MODE
{
	DRAW_TRIANGLES = 0,
	DRAW_TRIANGLE_STRIP,
	DRAW_LINES,
	DRAW_FAN,
	DRAW_MODE_LAST,
};

class RenderComponent : public Component
{
public:
	RenderComponent(Entity* parent, OBJInfo info, unsigned int textureID, DRAW_MODE mode = DRAW_TRIANGLES);
	RenderComponent(Entity* parent);
	RenderComponent();
	~RenderComponent();


	/* Initialized by RenderSystem*/
	void setBufferObjects(const unsigned int& VBO, const unsigned int& EBO);
	

	/* Needed for Rendering */
	OBJInfo& getInfo();
	DRAW_MODE getMode();
	unsigned int getVBO();
	unsigned int getEBO();
	unsigned int getTexID();



private:
	DRAW_MODE mode;
	OBJInfo info;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int textureID;
};

#endif