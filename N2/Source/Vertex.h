#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

class Vertex {

public:

	Vertex(Vector3 position, Vector3 texCoord, Vector3 normal);
	Vertex();
	~Vertex();
	bool operator < (const Vertex other) const;
	void setPos(const Vector3& pos);
	void setNormal(const Vector3& normal);
	void setTexCoord(const Vector3& texCoord);
	void setAll(const Vector3& pos, const Vector3& texCoord, const Vector3& normal);

private:
	Vector3 position;
	Vector3 normal;
	Vector3 texCoord;
};

#endif
