#include "LightSource.h"


unsigned int LightSource::count = 0;

LightSource::LightSource(LIGHT_TYPE type)
{
	this->type = type;
	id = count++;
	//position.SetZero();
	//color.Set(1, 1, 1);
	//power = 1.0f;
	//kC = 1.0f;
	//kL = 0.0f;
	//kQ = 0.0f;
	//spotDirection.Set(0.0f, 1.0f, 0.0f);
	//exponent = 3.0f;
	//cosCutoff = cos(Math::DegreeToRadian(45));
	//cosInner = cos(Math::DegreeToRadian(30));
}

LightSource::LightSource()
{
	
}


LightSource::~LightSource()
{
	count--;
}

void LightSource::setPointLight(const Vector3& position, const Vector3& color, const float& power, 
	const float& kC, const float& kL, const float& kQ)
{
	this->position = position;
	this->color = color;
	this->power = power;
	this->kC = kC;
	this->kL = kL;
	this->kQ = kQ;
}

void LightSource::setDirLight(const Vector3& direction, const Vector3& color, const float& power)
{
	this->position = direction;
	this->color = color;
	this->power = power;
}

void LightSource::setSpotLight(const Vector3& position, const Vector3& color, const Vector3& spotDirection, 
	const float& power, const float& cosCutoff, const float& cosInner, const float& exponent, 
	const float& kC, const float& kL, const float& kQ)
{
	this->position = position;
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
	this->position = position;
}

void LightSource::setPower(const float& power)
{
	this->power = power;
}

void LightSource::setColor(const Vector3& color)
{
	this->color = color;
}

void LightSource::setSpotlightDir(const Vector3& spotDirection)
{
	this->spotDirection = spotDirection;
}


void LightSource::setupAttribs(ShaderProgram* shader)
{
	shader->Use();
	shader->setInt(getPropertyName("type"), type);
	shader->setBool("lightEnabled", true);

	if (type == LIGHT_POINT || type == LIGHT_SPOTLIGHT)
	{
		shader->setFloat(getPropertyName("kC"), kC);
		shader->setFloat(getPropertyName("kL"), kL);
		shader->setFloat(getPropertyName("kQ"), kQ);

		if (type == LIGHT_SPOTLIGHT)
		{
			//shader->setVec3(getPropertyName("spotDirection"), spotDirection);
			shader->setFloat(getPropertyName("cosCutoff"), cos(Math::DegreeToRadian(cosCutoff)));
			shader->setFloat(getPropertyName("cosInner"), cos(Math::DegreeToRadian(cosInner)));
			shader->setFloat(getPropertyName("exponent"), exponent);
		}
	}
}

void LightSource::updateAttribs(ShaderProgram* shader, const MS& viewStack)
{
	shader->Use();
	shader->setVec3(getPropertyName("position"), position);
	shader->setVec3(getPropertyName("color"), color);
	shader->setFloat(getPropertyName("power"), power);

	if(type == LIGHT_SPOTLIGHT)
		shader->setVec3(getPropertyName("spotDirection"), spotDirection);
}


unsigned int & LightSource::getCount()
{
	return count;
}

std::string LightSource::getPropertyName(const std::string& propertyName) const
{
	return "lights[" + std::to_string(id) + "]." + propertyName;
}
