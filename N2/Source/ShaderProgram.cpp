#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
{

	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;

	id = glCreateProgram();
	unsigned int vShader = loadAndCompile(GL_VERTEX_SHADER, vertexPath);
	unsigned int fShader = loadAndCompile(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(id, vShader);
	glAttachShader(id, fShader);
	glLinkProgram(id);
	glValidateProgram(id);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

}

void ShaderProgram::Use()
{
	glUseProgram(id);
}



unsigned int ShaderProgram::loadAndCompile(unsigned int type, const std::string &filePath)
{
	std::ifstream handle(filePath);
	std::string line = "";
	std::string source = "";

	if (!handle.is_open())
		std::cout << "[Error] Could not load shader: " << filePath << std::endl;

	while (std::getline(handle, line))
		source += line + "\n";

	handle.close();


	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	// ShaderProgram Creation Validity
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "[Error] Could not compile " << ((type == GL_VERTEX_SHADER) ? "Vertex shader!" : "Fragment shader!") << " (" << filePath << ")" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setVec3(const std::string &name, Vector3 vec) const
{
	setVec3(name, vec.x, vec.y, vec.z);
}


void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	int attrid = glGetUniformLocation(id, name.c_str());
	glUniform4f(attrid, x, y, z, w);
}

void ShaderProgram::setMat4(const std::string &name, Mtx44 matrix) const
{
	unsigned int attrid = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(attrid, 1, false, &matrix.a[0]);
}

const std::string& ShaderProgram::getVertexPath() const
{
	return vertexPath;
}

const std::string& ShaderProgram::getFragmentPath() const
{
	return fragmentPath;
}