#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Vector3.h"
#include "ShaderProgram.h"

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

	void setPointLight(const Vector3& positionCameraSpace, const Vector3& color, const float& power,
		const float& kC, const float& kL, const float& kQ);
	
	void setDirLight(const Vector3& positionCameraSpace, const Vector3& color, const float& power);
	void setSpotLight(const Vector3& positionCameraSpace, const Vector3& color, const Vector3& spotDirection,
		const float& power, const float& cosCutoff, const float& cosInner, const float& exponent,
		const float& kC, const float &kL, const float& kQ);

	void setPosition(const Vector3& position);

	void updateAttribs(ShaderProgram* shader);

private:

	const std::string& getPropertyName(const std::string& propertyName) const;

	unsigned int id;
	static unsigned int count;

	LIGHT_TYPE type;
	Vector3 positionCameraSpace;
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