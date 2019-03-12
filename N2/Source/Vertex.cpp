#include "Vertex.h"



Vertex::Vertex(Vector3 position, Vector3 texCoord, Vector3 normal)
{
	this->position = position;
	this->normal = normal;
	this->texCoord = texCoord;
}

Vertex::Vertex()
{
	position.SetZero();
	normal.SetZero();
	texCoord.SetZero();

}

Vertex::~Vertex()
{

}

bool Vertex::operator < (const Vertex other) const
{
	return memcmp((void*)this, (void*)&other, sizeof(Vertex)) > 0;
}

void Vertex::setPos(const Vector3 & pos)
{
	this->position = pos;
}

void Vertex::setNormal(const Vector3 & normal)
{
	this->normal = normal;
}

void Vertex::setTexCoord(const Vector3 & texCoord)
{
	this->texCoord = texCoord;
}

void Vertex::setAll(const Vector3 & pos,const Vector3 & texCoord, const Vector3 & normal)
{
	this->position = pos;
	this->normal = normal;
	this->texCoord = texCoord;
}

const Vector3& Vertex::getPos() const
{
	return position;
}
