#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this -> pos = pos;
	}
protected:
private:
	glm::vec3 pos;
};
class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();
	void Draw();
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	enum
	{
		POSITION_VB,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	unsigned int _drawCount;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];
};

