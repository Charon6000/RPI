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

## Klasa Shader

Klasa `Shader` zarządza shaderami w OpenGL, w tym ich ładowaniem, kompilacją i wiązaniem do programu renderującego. Pozwala na ładowanie shaderów z pliku i korzystanie z nich w aplikacji.

### `Shader(const std::string& fileName)`
Konstruktor klasy `Shader`. Tworzy program shaderów, ładując pliki z shaderami, kompilując je i wiążąc z programem OpenGL.

- **Parametry**:
  - `fileName`: Ścieżka do pliku z kodem shadera, który zostanie załadowany.

### `void Bind()`
Wiąże program shaderów do aktualnego kontekstu renderowania, umożliwiając jego użycie w dalszych operacjach rysowania.

### `~Shader()`
Destruktor klasy `Shader`. Usuwa program shaderów i zwalnia zasoby związane z OpenGL.

## Szczegóły implementacji

- **LoadShader**: Funkcja prywatna `LoadShader` ładuje zawartość pliku shadera do tekstu.
- **CheckShaderError**: Funkcja `CheckShaderError` sprawdza, czy podczas kompilacji lub linkowania wystąpiły błędy, a następnie wyświetla odpowiedni komunikat o błędzie.
- **CreateShader**: Funkcja `CreateShader` tworzy i kompiluje shader, a następnie zwraca jego identyfikator.

## Prywatne metody

- **`Shader(const Shader& other)`**  
  Konstruktor kopiujący (zablokowany w celu uniemożliwienia kopiowania obiektu Shader).

- **`void operator=(const Shader& other)`**  
  Operator przypisania (zablokowany w celu uniemożliwienia przypisania).

## Stałe

- **NUM_SHADER**: Liczba shaderów, które mogą być załadowane do programu. Ustalona na 2 (np. vertex shader i fragment shader).

## Atrybuty prywatne

- **`GLuint _program`**: Identyfikator programu shaderów w OpenGL.
- **`GLuint _shaders[NUM_SHADER]`**: Tablica identyfikatorów shaderów, przechowująca różne typy shaderów wykorzystywane w programie.