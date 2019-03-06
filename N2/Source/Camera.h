#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Mtx44.h"

class Camera
{
public:


	Camera(Vector3 position);
	Camera();
	~Camera();

	Mtx44 LookAt();
	void Reset();
	void Update(double dt);
	void Invert();
	void setFreeLook(bool state);

	Vector3 getPos();
	Vector3 getRight();
	Vector3 getFront();
	float getYaw();

private:

	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 front;

	bool firstMouse;
	bool canFreeLook;
	double lastX = 0.0;
	double lastY = 0.0;
	float sensitivity = 0.08f;
	float yaw = -90.0f;
	float pitch = 0.0f;

	void updateMouse();

};

#endif



