#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
	{
		this -> pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }


protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};
class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices );
	Mesh(const std::string fileName);
	virtual ~Mesh();
	void Draw();

	const std::vector<glm::vec3>& GetVertices() const;
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	std::vector<glm::vec3> vertices;

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	unsigned int _drawCount;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];
};

