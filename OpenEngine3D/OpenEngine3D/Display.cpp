#include "Display.h"
#include <iostream>
#include<GL/glew.h>
#include "Camera.h"
#include "imgui/imgui_impl_sdl2.h"

// Konstruktor: Inicjalizuje okno wy�wietlania oraz kontekst OpenGL

Display::Display(int width, int height, const std::string& title)
{
    _width = width;
    _height = height;
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

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Czy�ci bufor koloru
}

// IsClosed: Sprawdza, czy okno zosta�o zamkni�te
bool Display::IsClosed() { return _isClosed; }

int Display::AxisX() { return currentMouseX; }

int Display::AxisY() { return currentMouseY; }

bool Display::isDragging() { return _isDragging; }

bool Display::isRotating() { return _isRotating; }

void Display::ResetScroolOffset() { _scrollOffset = 0; }

// Update: Aktualizuje okno, obs�uguje zdarzenia i wymienia bufory
void Display::Update()
{
    SDL_GL_SwapWindow(_window);
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        SDL_GetMouseState(&currentMouseX, &currentMouseY);
        ImGui_ImplSDL2_ProcessEvent(&e);
        _scrollOffset = 0;
        if (e.type == SDL_QUIT)
            _isClosed = true;
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            _width = e.window.data1;
            _height = e.window.data2;
            glViewport(0, 0, _width, _height);
        }
        else if (e.type == SDL_MOUSEWHEEL) {
            _scrollOffset = e.wheel.y;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            _isDragging = true;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
            _isDragging = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT) {
            _isRotating = true;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT) {
            _isRotating = false;
        }
    }
}