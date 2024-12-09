#include "Display.h"
#include <iostream>
#include<GL/glew.h>

// Konstruktor: Inicjalizuje okno wy�wietlania oraz kontekst OpenGL
Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING); // Inicjalizuje wszystkie systemy SDL

    // Ustawienia atrybut�w kontekstu OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);   // 8 bit�w dla czerwonego kana�u
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 8 bit�w dla zielonego kana�u
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);  // 8 bit�w dla niebieskiego kana�u
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bity na ca�y bufor kolor�w
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // W��czenie podw�jnego buforowania

    // Tworzy okno SDL z mo�liwo�ci� u�ywania OpenGL
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // Tworzy kontekst OpenGL dla okna
    _glcontext = SDL_GL_CreateContext(_window);

    // Inicjalizuje GLEW i sprawdza, czy si� powiod�o
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    _isClosed = false; // Okno jest otwarte na pocz�tku
}

// Destruktor: Usuwa okno i kontekst OpenGL oraz zamyka SDL
Display::~Display()
{
    SDL_GL_DeleteContext(_glcontext); // Usuwa kontekst OpenGL
    SDL_DestroyWindow(_window);       // Niszczy okno SDL
    SDL_Quit();                       // Zamyka SDL
}

// SetColor: Ustawia kolor t�a i czy�ci bufor koloru
void Display::SetColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);        // Ustawia kolor czyszczenia t�a
    glClear(GL_COLOR_BUFFER_BIT);    // Czy�ci bufor koloru
}

// IsClosed: Sprawdza, czy okno zosta�o zamkni�te
bool Display::IsClosed()
{
    return _isClosed;
}

// Update: Aktualizuje okno, obs�uguje zdarzenia i wymienia bufory
void Display::Update()
{
    SDL_GL_SwapWindow(_window); // Wymienia bufory w celu aktualizacji wy�wietlania

    SDL_Event e;
    while (SDL_PollEvent(&e)) // Obs�uguje zdarzenia SDL
    {
        if (e.type == SDL_QUIT) // Sprawdza, czy u�ytkownik zamkn�� okno
            _isClosed = true;   // Oznacza okno jako zamkni�te
    }
}
