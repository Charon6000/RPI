#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	_drawCount = numVertices;

	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glBindVertexArray(0);
}