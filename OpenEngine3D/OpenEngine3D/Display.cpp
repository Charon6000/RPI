#include "Display.h"
#include <iostream>
#include<GL/glew.h>

// Konstruktor: Inicjalizuje okno wyœwietlania oraz kontekst OpenGL
Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING); // Inicjalizuje wszystkie systemy SDL

    // Ustawienia atrybutów kontekstu OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);   // 8 bitów dla czerwonego kana³u
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 8 bitów dla zielonego kana³u
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);  // 8 bitów dla niebieskiego kana³u
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bity na ca³y bufor kolorów
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // W³¹czenie podwójnego buforowania

    // Tworzy okno SDL z mo¿liwoœci¹ u¿ywania OpenGL
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // Tworzy kontekst OpenGL dla okna
    _glcontext = SDL_GL_CreateContext(_window);

    // Inicjalizuje GLEW i sprawdza, czy siê powiod³o
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    _isClosed = false; // Okno jest otwarte na pocz¹tku
}

// Destruktor: Usuwa okno i kontekst OpenGL oraz zamyka SDL
Display::~Display()
{
    SDL_GL_DeleteContext(_glcontext); // Usuwa kontekst OpenGL
    SDL_DestroyWindow(_window);       // Niszczy okno SDL
    SDL_Quit();                       // Zamyka SDL
}

// SetColor: Ustawia kolor t³a i czyœci bufor koloru
void Display::SetColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);        // Ustawia kolor czyszczenia t³a
    glClear(GL_COLOR_BUFFER_BIT);    // Czyœci bufor koloru
}

// IsClosed: Sprawdza, czy okno zosta³o zamkniête
bool Display::IsClosed()
{
    return _isClosed;
}

// Update: Aktualizuje okno, obs³uguje zdarzenia i wymienia bufory
void Display::Update()
{
    SDL_GL_SwapWindow(_window); // Wymienia bufory w celu aktualizacji wyœwietlania

    SDL_Event e;
    while (SDL_PollEvent(&e)) // Obs³uguje zdarzenia SDL
    {
        if (e.type == SDL_QUIT) // Sprawdza, czy u¿ytkownik zamkn¹³ okno
            _isClosed = true;   // Oznacza okno jako zamkniête
    }
}
