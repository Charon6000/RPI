#include "Mesh.h"
#include <vector>

// Konstruktor: Inicjalizuje siatk� z wierzcho�kami i przygotowuje j� do renderowania
Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
    _drawCount = numVertices; // Liczba wierzcho�k�w do narysowania

    // Tworzy obiekt tablicy wierzcho�k�w
    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    // Wektory przechowuj�ce pozycje i wsp�rz�dne tekstur wierzcho�k�w
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    // Rezerwuje miejsce w pami�ci dla wierzcho�k�w
    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    // Wype�nia wektory danymi wierzcho�k�w
    for (unsigned int i = 0; i < numVertices; i++)
    {
        positions.push_back(*vertices[i].GetPos());        // Dodaje pozycj� wierzcho�ka
        texCoords.push_back(*vertices[i].GetTexCoord());  // Dodaje wsp�rz�dne tekstury
    }

    // Tworzy i wype�nia bufor pozycji wierzcho�k�w
    glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

    // W��cza i przypisuje atrybut pozycji (indeks 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Tworzy i wype�nia bufor wsp�rz�dnych tekstur
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

    // W��cza i przypisuje atrybut tekstur (indeks 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Od��cza tablic� wierzcho�k�w
    glBindVertexArray(0);
}

// Destruktor: Usuwa obiekty OpenGL zwi�zane z siatk�
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vertexArrayObject); // Usuwa tablic� wierzcho�k�w
}

// Draw: Renderuje siatk� na ekranie
void Mesh::Draw()
{
    glBindVertexArray(_vertexArrayObject);          // Wi��e tablic� wierzcho�k�w
    glDrawArrays(GL_TRIANGLES, 0, _drawCount);      // Rysuje siatk� jako tr�jk�ty
    glBindVertexArray(0);                           // Od��cza tablic� wierzcho�k�w
}
