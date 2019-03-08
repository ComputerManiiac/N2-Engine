#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <GL\glew.h>
#include "Component.h"
#include "OBJInfo.h"
#include "Material.h"

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
	const OBJInfo& getInfo() const;
	const DRAW_MODE& getMode() const;
	const Material& getMaterial() const;
	const unsigned int& getVBO() const;
	const unsigned int& getEBO() const;
	const unsigned int& getTexID() const;



private:
	DRAW_MODE mode;
	Material material;
	OBJInfo info;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int textureID;
};

#endif