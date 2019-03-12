#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Vector3.h"
#include "ShaderProgram.h"
#include "MatrixStack.h"
#include <iostream>
#include <string>

enum LIGHT_TYPE {
	LIGHT_POINT = 0,
	LIGHT_DIRECTIONAL = 1,
	LIGHT_SPOTLIGHT = 2,

};



class LightSource
{
public:

	LightSource(LIGHT_TYPE type);
	LightSource();
	~LightSource();

	void setPointLight(const Vector3& position, const Vector3& color, const float& power,
		const float& kC, const float& kL, const float& kQ);
	
	void setDirLight(const Vector3& direction, const Vector3& color, const float& power);
	void setSpotLight(const Vector3& position, const Vector3& color, const Vector3& spotDirection,
		const float& power, const float& cosCutoff, const float& cosInner, const float& exponent,
		const float& kC, const float &kL, const float& kQ);

	void setPosition(const Vector3& position);
	void setPower(const float& power);
	void setColor(const Vector3& color);
	void setSpotlightDir(const Vector3& direction);

	void setupAttribs(ShaderProgram* shader);
	void updateAttribs(ShaderProgram* shader, const MS& viewStack);

	static unsigned int& getCount();

private:

	std::string getPropertyName(const std::string& propertyName) const;

	unsigned int id;
	static unsigned int count;

	LIGHT_TYPE type;
	Vector3 position;
	Vector3 color;
	float power;
	float kC;
	float kL;
	float kQ;

	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};

#endif