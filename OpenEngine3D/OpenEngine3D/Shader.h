#pragma once
#include <string>
#include <GL/glew.h>
class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADER = 2;
	Shader(const Shader& other) {}
	void operator = (const Shader& other) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);


	GLuint _program;
	GLuint _shaders[NUM_SHADER];
};