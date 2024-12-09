#include "Mesh.h"
#include <vector>

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
}

// Destruktor: Usuwa obiekty OpenGL zwi¹zane z siatk¹
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vertexArrayObject); // Usuwa tablicê wierzcho³ków
}

// Draw: Renderuje siatkê na ekranie
void Mesh::Draw()
{
    glBindVertexArray(_vertexArrayObject);          // Wi¹¿e tablicê wierzcho³ków
    glDrawArrays(GL_TRIANGLES, 0, _drawCount);      // Rysuje siatkê jako trójk¹ty
    glBindVertexArray(0);                           // Od³¹cza tablicê wierzcho³ków
}
