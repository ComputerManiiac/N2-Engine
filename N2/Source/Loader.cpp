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

OBJInfo Loader::loadOBJ(const std::string & filePath)
{
	std::ifstream handle(filePath);
	if (!handle.is_open())
	{
		std::cout << "[ERROR] Could not load OBJ file at " << filePath << " ! Invalid directory?" << std::endl;
		return OBJInfo();
	}


	// Input
	std::string line;
	char buffer[256];
	std::vector<Vector3> texCoords;
	std::vector<Vector3> normals;
	std::vector<Vector3> positions;

	// Stores the index of each vertex (position, texCoord and normal) of each triangle 
	// where index = position+1
	// Index is the position of the specific attribute in its respective vector, but incremented by 1 
	// since vector starts from 0 while obj file starts from 1
	std::vector<unsigned int> vertIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;


	while (!handle.eof()){

		handle.getline(buffer, 256);
		Vector3 vertex;

		// Vertex
		if (strncmp("v ", buffer, 2) == 0)
		{
			sscanf_s((buffer + 2), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
			positions.push_back(vertex);
		}

		// Texture Coordinate
		else if (strncmp("vt ", buffer, 3) == 0)
		{
			sscanf_s((buffer + 3), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
			texCoords.push_back(vertex);
		}

		// Vertex Normal
		else if (strncmp("vn ", buffer, 3) == 0)
		{
			sscanf_s((buffer + 3), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
			normals.push_back(vertex);
		}

		// Face
		else if (strncmp("f ", buffer, 2) == 0)
		{
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];

			int matches = sscanf_s((buffer + 2), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2],
				&vertexIndex[3], &uvIndex[3], &normalIndex[3]);

			if (matches == 9 || matches == 12)
			{
				int sets = matches / 3;
				for (int i = 0; i < sets; i++)
				{
					vertIndices.push_back(vertexIndex[i]);
					uvIndices.push_back(uvIndex[i]);
					normalIndices.push_back(normalIndex[i]);
				}
			}
			else
			{
				std::cout << "[ERROR] This model contains " << matches << "-sided polygons! (" << filePath << ")" << std::endl;
				break;
			}
		}
	}

	handle.close();


	// Output
	std::map<Vertex, unsigned int> data;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Loop through all the indices
	for (unsigned int i = 0; i < (unsigned int)vertIndices.size(); i++)
	{
		unsigned int vertIndex = vertIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normIndex = normalIndices[i];

		// Index starts from 1 in obj file
		// Therefore, actual position in vector = Index - 1
		Vector3 pos = positions[vertIndex - 1];
		Vector3 uv = texCoords[uvIndex - 1];
		Vector3 norm = normals[normIndex - 1];

		Vertex v(pos, uv, norm);

		// Add the same index number if vertex already exists
		if (data.find(v) != data.end())
		{
			indices.push_back(data.at(v));
		}
		else
		{
			// If vertex, does not exist in collection yet, add it
			// and the corresponding index.
			vertices.push_back(v);
			unsigned int newIndex = ((unsigned int)vertices.size()) - 1;
			indices.push_back(newIndex);
			data[v] = newIndex;
		}
	}

	
	return OBJInfo(vertices, indices);
}


