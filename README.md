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

## Klasa BoundingSphere

Klasa `BoundingSphere` służy do reprezentowania sfery otaczającej (bounding sphere), która może być używana w różnych zastosowaniach, takich jak testy kolizji, optymalizacja przestrzenna czy analiza geometrii. 

Posiada funkcje:

### `BoundingSphere(const glm::vec3& center = glm::vec3(0), float radius = 0)`
Konstruktor klasy `BoundingSphere`. Tworzy sferę otaczającą na podstawie podanego środka i promienia.

- **Parametry**:
  - `center`: Wektor 3D (`glm::vec3`) określający środek sfery.
  - `radius`: Liczba zmiennoprzecinkowa (`float`) określająca promień sfery.

### `BoundingSphere(const std::vector<glm::vec3>& vertices)`
Konstruktor klasy `BoundingSphere`. Oblicza sferę otaczającą na podstawie zbioru wierzchołków. 

- **Parametry**:
  - `vertices`: Wektor (`std::vector`) zawierający wierzchołki jako obiekty `glm::vec3`.

## Szczegóły implementacji

- **center**: Atrybut przechowujący środek sfery jako trójwymiarowy wektor (`glm::vec3`).
- **radius**: Atrybut przechowujący promień sfery jako liczbę zmiennoprzecinkową (`float`).
- **glm**: Klasa korzysta z funkcjonalności biblioteki GLM (OpenGL Mathematics) do obsługi operacji na wektorach i macierzach.

## Atrybuty publiczne

- **`glm::vec3 center`**: Wektor 3D reprezentujący środek sfery.
- **`float radius`**: Promień sfery.

## Przyszłe rozszerzenia

Możliwe do dodania metody:
- **Test kolizji**: Funkcja sprawdzająca, czy dwie sfery otaczające nakładają się na siebie.
- **Zmiana wymiarów**: Funkcja umożliwiająca dynamiczne skalowanie sfery.
- **Debugowanie**: Funkcja wizualizująca sferę w przestrzeni 3D przy użyciu OpenGL.

## Klasa Camera

Klasa `Camera` służy do zarządzania widokiem i projekcją w scenie 3D. Pozwala na definiowanie parametrów kamery, takich jak pole widzenia (FOV), proporcje ekranu (aspect ratio) oraz zakres rzutowania (zNear, zFar).

Posiada funkcje:

### `Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)`
Konstruktor klasy `Camera`. Tworzy kamerę na podstawie podanej pozycji, pola widzenia, proporcji ekranu oraz zakresu widoczności.

- **Parametry**:
  - `pos`: Wektor 3D (`glm::vec3`) określający pozycję kamery.
  - `fov`: Liczba zmiennoprzecinkowa (`float`) określająca pole widzenia kamery w stopniach.
  - `aspect`: Liczba zmiennoprzecinkowa (`float`) określająca proporcje szerokości do wysokości widoku.
  - `zNear`: Liczba zmiennoprzecinkowa (`float`) określająca najbliższą widoczną odległość.
  - `zFar`: Liczba zmiennoprzecinkowa (`float`) określająca najdalszą widoczną odległość.

### `glm::mat4 GetViewProjection() const`
Zwraca macierz widoku i projekcji, łącząc rzutowanie perspektywiczne z transformacją widoku kamery.

- **Zwraca**:
  - Macierz 4x4 (`glm::mat4`) reprezentującą widok i projekcję.

### `void setAspect(float aspect)`
Ustawia nowe proporcje ekranu i aktualizuje macierz projekcji perspektywicznej.

- **Parametry**:
  - `aspect`: Nowe proporcje szerokości do wysokości widoku.

## Szczegóły implementacji

- **m_perspective**: Macierz 4x4 (`glm::mat4`) przechowująca rzutowanie perspektywiczne.
- **m_position**: Wektor 3D (`glm::vec3`) określający pozycję kamery w przestrzeni.
- **m_forward**: Wektor 3D (`glm::vec3`) określający kierunek, w którym skierowana jest kamera.
- **m_up**: Wektor 3D (`glm::vec3`) określający kierunek "góry" kamery.
- **fov**: Pole widzenia kamery w stopniach.
- **aspect**: Proporcje szerokości do wysokości widoku.
- **zNear, zFar**: Zakres odległości widocznych w rzucie perspektywicznym.

## Atrybuty prywatne

- **`glm::mat4 m_perspective`**: Macierz rzutowania perspektywicznego.
- **`glm::vec3 m_position`**: Pozycja kamery.
- **`glm::vec3 m_forward`**: Kierunek, w którym patrzy kamera.
- **`glm::vec3 m_up`**: Kierunek "góry" kamery.
- **`float fov`**: Pole widzenia kamery.
- **`float aspect`**: Proporcje widoku.
- **`float zNear`**: Najbliższa widoczna odległość.
- **`float zFar`**: Najdalsza widoczna odległość.

## Przyszłe rozszerzenia

Możliwe do dodania metody:
- **Ruch kamery**: Funkcje umożliwiające poruszanie kamerą w przestrzeni 3D.
- **Rotacja kamery**: Funkcje do obracania kamery wokół osi.
- **Debugowanie**: Wizualizacja frustum kamery w przestrzeni 3D.

## Klasa ObjLoader

Klasa `ObjLoader` obsługuje ładowanie modeli 3D w formacie OBJ. Pozwala na parsowanie plików OBJ, generowanie indeksowanego modelu oraz obliczanie normalnych dla wierzchołków.

### Struktura `OBJIndex`

Struktura pomocnicza przechowująca informacje o indeksach wierzchołków, tekstur i normalnych:

- **Atrybuty**:
  - `unsigned int vertexIndex`: Indeks wierzchołka.
  - `unsigned int uvIndex`: Indeks współrzędnych tekstury.
  - `unsigned int normalIndex`: Indeks wektora normalnego.

- **Operator**:
  - `bool operator<(const OBJIndex& r) const`: Porównuje obiekty `OBJIndex` na podstawie indeksu wierzchołka.

### Klasa `IndexedModel`

Reprezentuje model indeksowany gotowy do renderowania.

- **Atrybuty**:
  - `std::vector<glm::vec3> positions`: Lista pozycji wierzchołków.
  - `std::vector<glm::vec2> texCoords`: Lista współrzędnych tekstur.
  - `std::vector<glm::vec3> normals`: Lista wektorów normalnych.
  - `std::vector<unsigned int> indices`: Lista indeksów wierzchołków.

- **Metody**:
  - `void CalcNormals()`: Oblicza wektory normalne dla wierzchołków na podstawie ich indeksów i pozycji.

### Klasa `OBJModel`

Obsługuje parsowanie danych z plików OBJ i konwersję na model indeksowany.

- **Atrybuty publiczne**:
  - `std::vector<OBJIndex> OBJIndices`: Lista indeksów OBJ.
  - `std::vector<glm::vec3> vertices`: Lista wierzchołków.
  - `std::vector<glm::vec2> uvs`: Lista współrzędnych tekstur.
  - `std::vector<glm::vec3> normals`: Lista wektorów normalnych.
  - `bool hasUVs`: Flaga wskazująca obecność współrzędnych tekstur.
  - `bool hasNormals`: Flaga wskazująca obecność normalnych.

- **Konstruktor**:
  - `OBJModel(const std::string& fileName)`: Wczytuje dane z pliku OBJ i inicjalizuje struktury.

    - **Parametry**:
      - `fileName`: Ścieżka do pliku OBJ w postaci łańcucha znaków (`std::string`).

- **Metody publiczne**:
  - `IndexedModel ToIndexedModel()`: Konwertuje dane modelu na obiekt klasy `IndexedModel`.

    - **Zwraca**: Obiekt zawierający pozycje, współrzędne tekstur, normalne oraz indeksy.

- **Metody prywatne**:
  - `unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result)`: Znajduje ostatni indeks wierzchołka.
  - `void CreateOBJFace(const std::string& line)`: Tworzy strukturę twarzy (face) na podstawie wiersza pliku OBJ.
  - `glm::vec2 ParseOBJVec2(const std::string& line)`: Parsuje współrzędne tekstury z linii.
  - `glm::vec3 ParseOBJVec3(const std::string& line)`: Parsuje wierzchołek lub normalną z linii.
  - `OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)`: Parsuje indeks z tokenu.

### Szczegóły implementacji

- **Biblioteka GLM**: Używana do operacji na wektorach i macierzach.
- **Format pliku OBJ**: Obsługiwane są elementy takie jak wierzchołki (v), tekstury (vt), normalne (vn) oraz twarze (f).
- **Obsługa wyjątków**: Należy zaimplementować odpowiednie mechanizmy walidacji danych w pliku OBJ.

### Przyszłe rozszerzenia

- **Obsługa materiałów (MTL)**: Wczytywanie i stosowanie materiałów do modeli.
- **Optymalizacja**: Usprawnienie procesu parsowania i konwersji na model indeksowany.
- **Debugowanie**: Wizualizacja załadowanych danych w przestrzeni 3D.

## Klasa Object

Klasa `Object` jest używana do reprezentacji obiektów 3D w scenie. Oferuje funkcjonalności do manipulacji transformacją obiektu, zarządzania jego właściwościami graficznymi oraz sprawdzania kolizji z innymi obiektami.

### Konstruktor

#### `Object(std::string nazwa, const std::string& tekstura, Transform transform, const std::string& mesh, const std::string& shader)`
Tworzy obiekt na podstawie podanych parametrów.

- **Parametry**:
  - `nazwa`: Nazwa obiektu w postaci ciągu znaków.
  - `tekstura`: Ścieżka do pliku tekstury.
  - `transform`: Transformacja początkowa obiektu (pozycja, rotacja, skala).
  - `mesh`: Ścieżka do pliku siatki obiektu.
  - `shader`: Ścieżka do pliku programu shader.

### Metody publiczne

#### `void Update(Camera& camera)`
Aktualizuje stan obiektu na podstawie kamery. Może obejmować renderowanie oraz obliczenia związane z transformacją obiektu.

- **Parametry**:
  - `camera`: Obiekt klasy `Camera` używany do obliczania widoku sceny.

#### `void SetPosition(glm::vec3 vector)`
Ustawia nową pozycję obiektu.

- **Parametry**:
  - `vector`: Wektor 3D (`glm::vec3`) reprezentujący nową pozycję obiektu.

#### `void SetRotation(glm::vec3 vector)`
Ustawia nową rotację obiektu.

- **Parametry**:
  - `vector`: Wektor 3D (`glm::vec3`) reprezentujący nową rotację obiektu.

#### `void SetScale(glm::vec3 vector)`
Ustawia nową skalę obiektu.

- **Parametry**:
  - `vector`: Wektor 3D (`glm::vec3`) reprezentujący nową skalę obiektu.

#### `glm::vec3 GetPosition()`
Zwraca aktualną pozycję obiektu.

- **Zwraca**: Wektor 3D (`glm::vec3`) reprezentujący pozycję obiektu.

#### `glm::vec3 GetRotation()`
Zwraca aktualną rotację obiektu.

- **Zwraca**: Wektor 3D (`glm::vec3`) reprezentujący rotację obiektu.

#### `glm::vec3 GetScale()`
Zwraca aktualną skalę obiektu.

- **Zwraca**: Wektor 3D (`glm::vec3`) reprezentujący skalę obiektu.

#### `bool CheckCollision(const Object& other)`
Sprawdza, czy obiekt koliduje z innym obiektem.

- **Parametry**:
  - `other`: Inny obiekt klasy `Object`, z którym kolizja jest sprawdzana.
- **Zwraca**: `true`, jeśli obiekty kolidują; w przeciwnym razie `false`.

### Atrybuty publiczne

- **`glm::vec3 velocity`**: Wektor prędkości obiektu.

### Atrybuty prywatne

- **`Texture _texture`**: Tekstura obiektu.
- **`Transform _transform`**: Transformacja obiektu (pozycja, rotacja, skala).
- **`Mesh _mesh`**: Siatka obiektu.
- **`Shader _shader`**: Shader używany do renderowania obiektu.
- **`std::string _nazwa`**: Nazwa obiektu.
- **`BoundingSphere _boundingSphere`**: Sfera ograniczająca używana do sprawdzania kolizji.

### Przyszłe rozszerzenia

- **Fizyka**: Dodanie bardziej zaawansowanych obliczeń fizycznych, takich jak grawitacja czy siły zewnętrzne.
- **Interakcje**: Umożliwienie interakcji pomiędzy obiektami.
- **Animacje**: Wsparcie dla animowanych siatek i tekstur.


## Klasa Rigidbody

Klasa `Rigidbody` jest używana do reprezentowania obiektów fizycznych w przestrzeni 3D, które podlegają ruchowi i grawitacji. Umożliwia aktualizowanie stanu obiektu na podstawie upływającego czasu oraz wyświetlanie go w scenie.

### Konstruktor

#### `Rigidbody(float posX, float posY, float posZ)`
Tworzy obiekt `Rigidbody` na podstawie podanych współrzędnych pozycji.

- **Parametry**:
  - `posX`: Współrzędna X pozycji obiektu w przestrzeni 3D.
  - `posY`: Współrzędna Y pozycji obiektu w przestrzeni 3D.
  - `posZ`: Współrzędna Z pozycji obiektu w przestrzeni 3D.

### Metody publiczne

#### `void Update(float deltaTime)`
Aktualizuje stan obiektu na podstawie upływającego czasu (deltaTime). Umożliwia m.in. obliczenie nowej pozycji obiektu uwzględniającej jego prędkość i działającą na niego grawitację.

- **Parametry**:
  - `deltaTime`: Czas, który upłynął od ostatniej klatki, w sekundach. Używane do obliczeń ruchu w czasie rzeczywistym.

#### `void Draw()`
Rysuje obiekt w przestrzeni 3D. Metoda ta może być używana do wyświetlania obiektu w scenie, zależnie od implementacji graficznej.

### Atrybuty publiczne

- **`float x, y, z`**: Pozycja obiektu w przestrzeni 3D.
- **`float velocityX, velocityY, velocityZ`**: Prędkości obiektu w kierunkach X, Y i Z.
- **`float gravity`**: Wartość grawitacji (przyspieszenia) działającej na obiekt.

### Przyszłe rozszerzenia

- **Symulacja grawitacji**: Możliwość dostosowania siły grawitacji dla różnych obiektów.
- **Interakcje fizyczne**: Dodanie wykrywania kolizji i reagowania na inne obiekty fizyczne.
- **Ruch zaawansowany**: Wsparcie dla bardziej zaawansowanych typów ruchu, takich jak obrót czy siły zewnętrzne.

## Klasa Texture

Klasa `Texture` jest używana do reprezentowania tekstur w aplikacjach graficznych, szczególnie w kontekście renderowania przy użyciu OpenGL. Umożliwia ładowanie tekstur z plików oraz wiązanie ich do jednostek tekstur w procesie renderowania.

### Konstruktor

#### `Texture(const std::string& fileName)`
Tworzy obiekt tekstury na podstawie podanego pliku.

- **Parametry**:
  - `fileName`: Ścieżka do pliku tekstury, który ma zostać załadowany.

### Metody publiczne

#### `void Bind(unsigned int unit)`
Więże teksturę z określoną jednostką tekstury w OpenGL, aby mogła być używana w procesie renderowania.

- **Parametry**:
  - `unit`: Jednostka tekstury, do której ma zostać przypisana tekstura (np. jednostka 0 dla podstawowej tekstury).

### Destruktor

#### `virtual ~Texture()`
Zwalnia zasoby zajmowane przez obiekt tekstury po jej użyciu.

### Metody prywatne

#### `Texture(const Texture& other)`
Konstruktor kopiujący – zabroniony (nie zaimplementowany).

#### `void operator=(const Texture& other)`
Operator przypisania – zabroniony (nie zaimplementowany).

### Atrybuty prywatne

- **`GLuint m_texture`**: Zmienna przechowująca identyfikator tekstury w OpenGL.

### Przyszłe rozszerzenia

- **Obsługa różnych formatów tekstur**: Rozszerzenie obsługi różnych typów plików tekstur (np. BMP, PNG, JPG).
- **Mipmapy**: Dodanie wsparcia dla generowania mipmap, co poprawi wydajność renderowania w przypadku tekstur o różnych rozmiarach.
- **Wieloelementowe tekstury**: Wsparcie dla tekstur w układzie wielowarstwowym lub tekstur 3D.

## Klasa Transform

Klasa `Transform` jest używana do reprezentowania transformacji obiektów 3D, w tym przesunięcia (pozycji), rotacji oraz skali. Umożliwia obliczanie macierzy modelu, które są wykorzystywane w procesie renderowania, oraz manipulowanie tymi transformacjami.

### Konstruktor

#### `Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))`
Tworzy obiekt transformacji na podstawie podanych parametrów.

- **Parametry**:
  - `pos`: Wektor 3D określający początkową pozycję obiektu.
  - `rot`: Wektor 3D określający początkową rotację obiektu w radianach (w każdej osi: X, Y, Z).
  - `scale`: Wektor 3D określający początkową skalę obiektu.

### Metody publiczne

#### `glm::mat4 GetModel() const`
Generuje macierz modelu 4x4 na podstawie transformacji obiektu (pozycja, rotacja, skala).

- **Zwraca**: Macierz 4x4 reprezentującą pełną transformację obiektu, uwzględniającą kolejność: skalowanie, obrót, a następnie przesunięcie.

#### `glm::vec3& GetPos()`
Zwraca referencję do wektora pozycji obiektu.

- **Zwraca**: Referencję do wektora 3D reprezentującego pozycję obiektu.

#### `glm::vec3& GetRot()`
Zwraca referencję do wektora rotacji obiektu.

- **Zwraca**: Referencję do wektora 3D reprezentującego rotację obiektu w radianach.

#### `glm::vec3& GetScale()`
Zwraca referencję do wektora skali obiektu.

- **Zwraca**: Referencję do wektora 3D reprezentującego skalę obiektu.

#### `void SetPos(const glm::vec3& pos)`
Ustawia nową pozycję obiektu.

- **Parametry**:
  - `pos`: Wektor 3D reprezentujący nową pozycję obiektu.

#### `void SetRot(const glm::vec3& rot)`
Ustawia nową rotację obiektu.

- **Parametry**:
  - `rot`: Wektor 3D reprezentujący nową rotację obiektu w radianach.

#### `void SetScale(const glm::vec3& scale)`
Ustawia nową skalę obiektu.

- **Parametry**:
  - `scale`: Wektor 3D reprezentujący nową skalę obiektu.

### Atrybuty prywatne

- **`glm::vec3 m_pos`**: Pozycja obiektu w przestrzeni 3D.
- **`glm::vec3 m_rot`**: Rotacja obiektu w przestrzeni 3D (w radianach).
- **`glm::vec3 m_scale`**: Skala obiektu w przestrzeni 3D.

### Przyszłe rozszerzenia

- **Transformacje w przestrzeni lokalnej**: Dodanie możliwości transformacji obiektów względem ich lokalnych układów współrzędnych.
- **Animacja**: Możliwość interpolacji pomiędzy różnymi stanami transformacji w czasie.
- **Złożone transformacje**: Dodanie funkcji umożliwiających bardziej zaawansowane transformacje, takie jak obrót wokół dowolnej osi.  
