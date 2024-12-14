#include "Mesh.h"
#include "obj_loader.h"
#include <vector>

<<<<<<< HEAD
// Konstruktor: Inicjalizuje siatkê z wierzcho³kami i przygotowuje j¹ do renderowania
Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
    _drawCount = numVertices; // Liczba wierzcho³ków do narysowania

    // Tworzy obiekt tablicy wierzcho³ków
    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    // Wektory przechowuj¹ce pozycje i wspó³rzêdne tekstur wierzcho³ków
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    // Rezerwuje miejsce w pamiêci dla wierzcho³ków
    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    // Wype³nia wektory danymi wierzcho³ków
    for (unsigned int i = 0; i < numVertices; i++)
    {
        positions.push_back(*vertices[i].GetPos());        // Dodaje pozycjê wierzcho³ka
        texCoords.push_back(*vertices[i].GetTexCoord());  // Dodaje wspó³rzêdne tekstury
    }

    // Tworzy i wype³nia bufor pozycji wierzcho³ków
    glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

    // W³¹cza i przypisuje atrybut pozycji (indeks 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Tworzy i wype³nia bufor wspó³rzêdnych tekstur
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

    // W³¹cza i przypisuje atrybut tekstur (indeks 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Od³¹cza tablicê wierzcho³ków
    glBindVertexArray(0);
=======
Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	 for (unsigned int i = 0; i < numVertices; i++) 
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}
	 for (unsigned int i = 0; i < numIndices; i++)
		 model.indices.push_back(indices[i]);
	 InitMesh(model);
>>>>>>> origin
}

// Destruktor: Usuwa obiekty OpenGL zwi¹zane z siatk¹
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vertexArrayObject); // Usuwa tablicê wierzcho³ków
}

<<<<<<< HEAD
// Draw: Renderuje siatkê na ekranie
void Mesh::Draw()
{
    glBindVertexArray(_vertexArrayObject);          // Wi¹¿e tablicê wierzcho³ków
    glDrawArrays(GL_TRIANGLES, 0, _drawCount);      // Rysuje siatkê jako trójk¹ty
    glBindVertexArray(0);                           // Od³¹cza tablicê wierzcho³ków
}
=======
void Mesh::InitMesh(const IndexedModel& model)
{
	_drawCount = model.indices.size();

	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glBindVertexArray(1);
}
>>>>>>> origin
