#ifndef LOADER_H
#define LOADER_H

#include <GL\glew.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include "OBJInfo.h"


class Loader
{
public:
	Loader();
	~Loader();
	static unsigned int loadTGA(const std::string& filePath);
	static OBJInfo loadOBJ(const std::string& filePath);
};

#endif