# RPI
* Dokumentacja: ``https://docs.google.com/document/d/16r9baTvD5L6q9c8by-x-md48kzLTodT6jtipIFAVy_s/edit``

# Wymagane programy
* Visual Studio Community
# Jak włączyć projekt
* Po sklonowaniu projektu wejdź do folderu RPI nastepnie OpenEngine3D i włącz plik OpenEngine3D.sln w programie Visual Studio Community

# Poruszanie się po programie:
## Klasa Display:
Klasa Display pozwala na wyświetlanie okna aplikacji.
Posiada funkcje:
* ``Display(<szerokość w pikselach>, <wysokość w pikselach>, <tytuł>)`` - tworzy okno i jego kontekst
* ``~Display()`` - Zamyka okno usuwając dane kontekstu i okna albo robi to po ręcznym zamknięciu okna
* ``SetColor(<red>, <green>, <blue>, <alpha>)``- Ustawia kolor tła okna
* ``IsClosed()`` - zwraca zmienną boolean w zależności czy okno jest zamknięte czy otwarte
* ``Update()`` - aktualizuje okno
## Klasa Mesh:

Klasa `Mesh` służy do przechowywania danych siatki 3D oraz renderowania jej przy użyciu OpenGL. Pozwala na tworzenie siatki z wierzchołków oraz rysowanie jej na ekranie.

Posiada funkcje

### `Mesh(Vertex* vertices, unsigned int numVertices)`
Konstruktor klasy `Mesh`. Tworzy siatkę na podstawie tablicy wierzchołków i liczby wierzchołków.

- **Parametry**:
  - `vertices`: wskaźnik na tablicę wierzchołków (`Vertex`).
  - `numVertices`: liczba wierzchołków w siatce.
  
### `~Mesh()`
Destruktor klasy `Mesh`. Zwalnia zasoby związane z OpenGL, takie jak bufory wierzchołków.

### `void Draw()`
Rysuje siatkę na ekranie, wykorzystując dane przechowywane w buforach OpenGL.

## Szczegóły implementacji

- **Vertex**: Klasa pomocnicza `Vertex` przechowuje pozycję wierzchołka jako trójwymiarowy wektor (`glm::vec3`).
- **Buffers**: Klasa `Mesh` używa buforów OpenGL do przechowywania danych wierzchołków (w zmiennej `_vertexArrayBuffers`) oraz zarządza ich rysowaniem za pomocą `_vertexArrayObject`.
  
## Prywatne metody

- **`Mesh(const Mesh& other)`**  
  Konstruktor kopiujący (zablokowany w celu uniemożliwienia kopiowania siatki).
  
- **`void operator=(const Mesh& other)`**  
  Operator przypisania (zablokowany w celu uniemożliwienia przypisania).

## Enums

- **POSITION_VB**: Zmienna wskazująca bufor pozycji wierzchołków.
- **NUM_BUFFERS**: Liczba buforów wykorzystywanych przez klasę.

## Atrybuty prywatne

- **`GLuint _vertexArrayObject`**: Identyfikator obiektu tablicy wierzchołków (VAO) OpenGL.
- **`GLuint _vertexArrayBuffers[NUM_BUFFERS]`**: Bufory przechowujące dane wierzchołków.
- **`unsigned int _drawCount`**: Liczba wierzchołków do narysowania.
