#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

// Konstruktor: £aduje teksturê z podanego pliku
Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;

    // Wczytuje plik obrazu i dekoduje go na surowe dane pikseli w formacie RGBA
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    // Sprawdza, czy wczytanie obrazu zakoñczy³o siê sukcesem
    if (imageData == NULL)
        std::cerr << "Nie uda³o siê za³adowaæ tekstury: " << fileName << std::endl;

    // Generuje obiekt tekstury i zapisuje jego ID w m_texture
    glGenTextures(1, &m_texture);

    // Wi¹¿e obiekt tekstury z celem tekstury 2D
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Ustawia tryb owijania tekstury dla osi S (poziomej) i T (pionowej)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Ustawia tryby filtrowania tekstury dla pomniejszania i powiêkszania
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // G³adkie skalowanie w dó³
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // G³adkie skalowanie w górê

    // Przesy³a dane pikseli do GPU i okreœla format tekstury
    glTexImage2D(
        GL_TEXTURE_2D,         // Typ docelowej tekstury
        0,                    // Poziom mipmapy (0 = poziom podstawowy)
        GL_RGBA,              // Wewnêtrzny format GPU
        width,                // Szerokoœæ tekstury
        height,               // Wysokoœæ tekstury
        0,                    // Obramowanie (musi byæ 0)
        GL_RGBA,              // Format danych pikseli
        GL_UNSIGNED_BYTE,     // Typ danych pikseli
        imageData             // WskaŸnik na dane pikseli
    );

    // Zwalnia surowe dane obrazu, poniewa¿ s¹ ju¿ przes³ane do GPU
    stbi_image_free(imageData);
}

// Destruktor: Usuwa obiekt tekstury
Texture::~Texture()
{
    // Usuwa obiekt tekstury, aby zwolniæ pamiêæ GPU
    glDeleteTextures(1, &m_texture);
}

// Bind: Aktywuje teksturê do u¿ycia w podanej jednostce tekstur
void Texture::Bind(unsigned int unit)
{
    // Upewnia siê, ¿e jednostka tekstur jest prawid³owa (OpenGL obs³uguje do 32 jednostek tekstur)
    assert(unit >= 0 && unit <= 31);

    // Aktywuje podan¹ jednostkê tekstur
    glActiveTexture(GL_TEXTURE0 + unit);

    // Wi¹¿e obiekt tekstury z aktualnie aktywn¹ jednostk¹ tekstur
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
