#ifndef LOADER_H
#define LOADER_H

#include <GL\glew.h>
#include <string>
#include <fstream>
#include <iostream>

class Loader
{
public:
	Loader();
	~Loader();
	static unsigned int loadTGA(const std::string& filePath);
};

#endif