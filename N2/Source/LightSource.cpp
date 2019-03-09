#include "LightSource.h"


unsigned int LightSource::count = 0;

LightSource::LightSource(LIGHT_TYPE type)
{
	this->type = type;
}

LightSource::LightSource()
{
	id = count++;
}


LightSource::~LightSource()
{
}

void LightSource::setPointLight(const Vector3& positionCameraSpace, const Vector3& color, const float& power, 
	const float& kC, const float& kL, const float& kQ)
{
	this->positionCameraSpace = positionCameraSpace;
	this->color = color;
	this->power = power;
	this->kC = kC;
	this->kL = kL;
	this->kQ = kQ;
}

void LightSource::setDirLight(const Vector3& positionCameraSpace, const Vector3& color, const float& power)
{
	this->positionCameraSpace = positionCameraSpace;
	this->color = color;
	this->power = power;
}

void LightSource::setSpotLight(const Vector3& positionCameraSpace, const Vector3& color, const Vector3& spotDirection, 
	const float& power, const float& cosCutoff, const float& cosInner, const float& exponent, 
	const float& kC, const float& kL, const float& kQ)
{
	this->positionCameraSpace = positionCameraSpace;
	this->color = color;
	this->spotDirection = spotDirection;
	this->power = power;
	this->cosCutoff = cosCutoff;
	this->cosInner = cosInner;
	this->exponent = exponent;
	this->kC = kC;
	this->kL = kL;
	this->kQ = kQ;
}

void LightSource::setPosition(const Vector3& position)
{
	this->positionCameraSpace = position;
}

void LightSource::updateAttribs(ShaderProgram* shader)
{
	shader->Use();
	shader->setVec3(getPropertyName("position_cameraspace"), positionCameraSpace);
	shader->setVec3(
}

const std::string& LightSource::getPropertyName(const std::string& propertyName) const
{
	return "lights[" + std::to_string(id) + "]." + propertyName;
}
