#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

// Konstruktor: �aduje tekstur� z podanego pliku
Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;

    // Wczytuje plik obrazu i dekoduje go na surowe dane pikseli w formacie RGBA
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    // Sprawdza, czy wczytanie obrazu zako�czy�o si� sukcesem
    if (imageData == NULL)
        std::cerr << "Nie uda�o si� za�adowa� tekstury: " << fileName << std::endl;

    // Generuje obiekt tekstury i zapisuje jego ID w m_texture
    glGenTextures(1, &m_texture);

    // Wi��e obiekt tekstury z celem tekstury 2D
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Ustawia tryb owijania tekstury dla osi S (poziomej) i T (pionowej)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Ustawia tryby filtrowania tekstury dla pomniejszania i powi�kszania
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // G�adkie skalowanie w d�
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // G�adkie skalowanie w g�r�

    // Przesy�a dane pikseli do GPU i okre�la format tekstury
    glTexImage2D(
        GL_TEXTURE_2D,         // Typ docelowej tekstury
        0,                    // Poziom mipmapy (0 = poziom podstawowy)
        GL_RGBA,              // Wewn�trzny format GPU
        width,                // Szeroko�� tekstury
        height,               // Wysoko�� tekstury
        0,                    // Obramowanie (musi by� 0)
        GL_RGBA,              // Format danych pikseli
        GL_UNSIGNED_BYTE,     // Typ danych pikseli
        imageData             // Wska�nik na dane pikseli
    );

    // Zwalnia surowe dane obrazu, poniewa� s� ju� przes�ane do GPU
    stbi_image_free(imageData);
}

// Destruktor: Usuwa obiekt tekstury
Texture::~Texture()
{
    // Usuwa obiekt tekstury, aby zwolni� pami�� GPU
    glDeleteTextures(1, &m_texture);
}

// Bind: Aktywuje tekstur� do u�ycia w podanej jednostce tekstur
void Texture::Bind(unsigned int unit)
{
    // Upewnia si�, �e jednostka tekstur jest prawid�owa (OpenGL obs�uguje do 32 jednostek tekstur)
    assert(unit >= 0 && unit <= 31);

    // Aktywuje podan� jednostk� tekstur
    glActiveTexture(GL_TEXTURE0 + unit);

    // Wi��e obiekt tekstury z aktualnie aktywn� jednostk� tekstur
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
