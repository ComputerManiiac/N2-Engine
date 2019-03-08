#include "OBJInfo.h"


OBJInfo::OBJInfo(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	this->vertices = std::move(vertices);
	this->indices = std::move(indices);
}


OBJInfo::OBJInfo()
{
}


OBJInfo::~OBJInfo()
{
}

const std::vector<Vertex>& OBJInfo::getVertices() const
{
	return vertices;
}

const std::vector<unsigned int>& OBJInfo::getIndices() const
{
	return indices;
}

OBJInfo OBJInfo::generateQuad()
{
	std::vector<Vertex> vertices;

	Vertex v;
	v.setNormal(Vector3(0, 0, 1));

	v.setPos(Vector3(-0.5, 0.5, 0));
	v.setTexCoord(Vector3(0, 1, 0));
	vertices.push_back(v);


	v.setPos(Vector3(-0.5, -0.5, 0));
	v.setTexCoord(Vector3(0, 0, 0));
	vertices.push_back(v);


	v.setPos(Vector3(0.5, 0.5, 0));
	v.setTexCoord(Vector3(1, 1, 0));
	vertices.push_back(v);


	v.setPos(Vector3(0.5, -0.5, 0));
	v.setTexCoord(Vector3(1, 0, 0));
	vertices.push_back(v);

	std::vector<unsigned int> indices = { 0,1,2,2,1,3 };

	return OBJInfo(vertices, indices);
}

OBJInfo OBJInfo::generateCube()
{
	std::vector<Vertex> vertices;
	Vertex v;
	v.setNormal(Vector3(0, 0, 1));

	v.setPos(Vector3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(v);

	v.setPos(Vector3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, 0.5f));
	vertices.push_back(v);

	v.setNormal(Vector3(1, 0, 0));

	v.setPos(Vector3(0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, -0.5f));
	vertices.push_back(v);


	v.setNormal(Vector3(0, 1, 0));

	v.setPos(Vector3(0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, 0.5f));
	vertices.push_back(v);



	v.setNormal(Vector3(1, 0, 0));

	v.setPos(Vector3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(v);

	v.setNormal(Vector3(0, -1, 0));

	v.setPos(Vector3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, 0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(v);

	v.setNormal(Vector3(0, 0, -1));
	
	v.setPos(Vector3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, 0.5f, -0.5f));
	vertices.push_back(v);
	v.setPos(Vector3(0.5f, -0.5f, -0.5f));
	vertices.push_back(v);

	std::vector<unsigned int> indices;
	for (int i = 0; i < (int)vertices.size(); i++)
		indices.push_back(i);

	return OBJInfo(vertices, indices);
}