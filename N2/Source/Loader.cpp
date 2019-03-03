#include "Loader.h"



Loader::Loader()
{
}


Loader::~Loader()
{
}


unsigned Loader::loadTGA(const std::string& filePath)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	if (!fileStream.is_open())
	{
		std::cout << "[ERROR] Failed to load TGA file at " << filePath << " ! Invalid directory?" << std::endl;
		return 0;
	}

	GLubyte		header[18];									// first 6 useful header bytes
	GLuint		bytesPerPixel;									// number of bytes per pixel in TGA gile
	GLuint		imageSize;										// for setting memory
	GLubyte*	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

	// Wrong bit compression format or invalid file
	if (width <= 0 || height <= 0 || (header[16] != 24 && header[16] != 32))
	{
		fileStream.close();							
		std::cout << "[ERROR] Failed to load TGA file at " << filePath << " ! Corrupted file?" << std::endl;
		return 0;
	}

	// Divide by 8 to get bytes per pixel
	bytesPerPixel = header[16] / 8;
	// Calculate memory required for TGA data
	imageSize = width * height * bytesPerPixel;	

	data = new GLubyte[imageSize];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Read alpha values if supported
	if (bytesPerPixel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);


	// Texture Settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Auto generate Mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);
	float maxAntisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAntisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAntisotropy);

	delete[] data;
	return texture;
}


