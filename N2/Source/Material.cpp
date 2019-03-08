#include "Material.h"



Material::Material(Vector3 diffuse, Vector3 specular, float shininess)
{
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Material::Material()
{
}


Material::~Material()
{
}


void Material::setDiffuse(const Vector3& diffuse)
{
	this->diffuse = diffuse;
}

void Material::setSpecular(const Vector3& specular)
{
	this->specular = specular;
}

void Material::setShininess(const float & shininess)
{
	this->shininess = shininess;
}

const Vector3& Material::getDiffuse() const
{
	return diffuse;
}

const Vector3& Material::getSpecular() const
{
	return specular;
}

const float& Material::getShininess() const
{
	return shininess;
}



