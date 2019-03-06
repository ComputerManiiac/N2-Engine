#ifndef OBJINFO_H
#define OBJINFO_H

#include "Vertex.h"
#include <vector>

class OBJInfo
{
public:
	OBJInfo(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	OBJInfo();
	~OBJInfo();

	std::vector<Vertex>* getVertices();
	std::vector<unsigned int>* getIndices();

	static OBJInfo generateQuad();
	static OBJInfo generateCube();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

#endif