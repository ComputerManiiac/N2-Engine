#include "OBJInfo.h"


OBJInfo OBJInfo::cube = OBJInfo();
OBJInfo OBJInfo::quad = OBJInfo();


OBJInfo::OBJInfo(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
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





OBJInfo OBJInfo::genQuad()
{
	if (quad.vertices.size() > 0)
		return quad;

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

OBJInfo OBJInfo::genCube()
{
	if (cube.vertices.size() > 0)
		return cube;

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

std::vector<Vector3> OBJInfo::genBoxCollider(const OBJInfo& obj)
{
	const std::vector<Vertex>& vertices = obj.getVertices();
	std::vector<Vector3> colliderPoints;
	Vector3 min, max;

	for (Vertex vert : vertices)
	{
		const Vector3& pos = vert.getPos();

		// Find the two extreme corners of the object
		if (pos.x < min.x)
			min.x = pos.x;
		if (pos.y < min.y)
			min.y = pos.y;
		if (pos.z < min.z)
			min.z = pos.z;

		if (pos.x > max.x)
			max.x = pos.x;
		if (pos.y > max.y)
			max.y = pos.y;
		if (pos.z > max.z)
			max.z = pos.z;
	}

	Vector3 v = min;
	colliderPoints.push_back(v);
	v = max;
	colliderPoints.push_back(v);

	v = min;
	v.x = max.x;
	colliderPoints.push_back(v);
	v = min;
	v.y = max.y;
	colliderPoints.push_back(v);
	v = min;
	v.z = max.z;
	colliderPoints.push_back(v);

	v = max;
	v.x = min.x;
	colliderPoints.push_back(v);
	v = max;
	v.y = min.y;
	colliderPoints.push_back(v);
	v = max;
	v.z = min.z;
	colliderPoints.push_back(v);



	return colliderPoints;
}


