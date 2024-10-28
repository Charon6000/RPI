#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName) 
{
    _program = glCreateProgram();
    _shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    _shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADER; i++)
        glAttachShader(_program, _shaders[i]);

    glBindAttribLocation(_program, 0,"position");
    glBindAttribLocation(_program, 1, "texCoord");

    glLinkProgram(_program);
    CheckShaderError(_program, GL_LINK_STATUS, true, "Program linking failed!:");
    glValidateProgram(_program);
    CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Program is invalid:");
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADER; i++)
    {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }

    glDeleteProgram(_program);
}

void Shader::Bind()
{
    glUseProgram(_program);
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);
    if (shader == 0)
        std::cerr << "Error: Shader creation failed" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLenghts[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLenghts[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLenghts);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compiling failed: ");

    return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
