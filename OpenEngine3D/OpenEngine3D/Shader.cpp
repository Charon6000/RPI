#include "Shader.h" 
#include <iostream>
#include <fstream>

// Konstruktor: £aduje i inicjalizuje program shaderowy
Shader::Shader(const std::string& fileName)
{
    // Tworzy pusty program shaderowy
    _program = glCreateProgram();

    // Tworzy i kompiluje shadery wierzcho³ków i fragmentów
    _shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    _shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    // Do³¹cza shadery do programu
    for (unsigned int i = 0; i < NUM_SHADER; i++)
        glAttachShader(_program, _shaders[i]);

    // Przypisuje atrybuty wejœciowe do programu
    glBindAttribLocation(_program, 0, "position");
    glBindAttribLocation(_program, 1, "texCoord");
    glBindAttribLocation(_program, 2, "normal");

    // £¹czy shadery w program i sprawdza b³êdy
    glLinkProgram(_program);
    CheckShaderError(_program, GL_LINK_STATUS, true, "Program linking failed!:");

    // Waliduje program shaderowy
    glValidateProgram(_program);
    CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Program is invalid:");


	// pobieranie uniformu z programu, odniesienie sie do niego
	_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");


}

// Destruktor: Usuwa shadery i program shaderowy
Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADER; i++)
    {
        // Od³¹cza i usuwa shadery
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }

    // Usuwa program shaderowy
    glDeleteProgram(_program);
}

// Bind: Aktywuje program shaderowy do u¿ycia
void Shader::Bind()
{
    glUseProgram(_program);
}


void Shader::Update(const Transform& transform, const Camera& camera)
{
    //nasz model
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	//update uniformu
    glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);

}

// CreateShader: Tworzy, kompiluje i sprawdza shader
GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    // Tworzy pusty obiekt shaderowy
    GLuint shader = glCreateShader(type);
    if (shader == 0)
        std::cerr << "Error: Shader creation failed" << std::endl;

    // Przygotowuje Ÿród³o shadera do kompilacji
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLenghts[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLenghts[0] = text.length();

    // Ustawia Ÿród³o i kompiluje shader
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLenghts);
    glCompileShader(shader);

    // Sprawdza b³êdy kompilacji
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compiling failed: ");

    return shader;
}

// LoadShader: £aduje kod shadera z pliku
std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        // Odczytuje linia po linii zawartoœæ pliku
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        // Informuje o b³êdzie, jeœli plik nie zosta³ otwarty
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

// CheckShaderError: Sprawdza b³êdy kompilacji lub walidacji shadera lub programu
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

        // Wyœwietla szczegó³owy komunikat o b³êdzie
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}