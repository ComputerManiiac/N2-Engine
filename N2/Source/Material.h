#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"

class Material
{
public:

	Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, float shininess);
	Material();
	~Material();

	void setAmbient(const Vector3& ambient);
	void setDiffuse(const Vector3& diffuse);
	void setSpecular(const Vector3& specular);
	void setShininess(const float& shininess);

	const Vector3& getAmbient() const;
	const Vector3& getDiffuse() const;
	const Vector3& getSpecular() const;
	const float& getShininess() const;
		
private:
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;
};

#endif