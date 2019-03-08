#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Mtx44.h"


class ShaderProgram
{
public:

	ShaderProgram(std::string vertexPath, std::string fragmentPath);

	void Use();
	
	unsigned int loadAndCompile(unsigned int type, const std::string &filePath);

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, Vector3 vec) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat4(const std::string &name, Mtx44 matrix) const;

	const std::string& getVertexPath() const;
	const std::string& getFragmentPath() const;

private:
	unsigned int id;
	std::string vertexPath = "";
	std::string fragmentPath = "";
};

#endif





