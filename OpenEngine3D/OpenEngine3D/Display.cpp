#include "Display.h"
#include <iostream>
#include <GL/glew.h>
#include "Camera.h"
#include "imgui/imgui_impl_sdl2.h"
#include <SDL2/SDL.h>

// Konstruktor: Inicjalizuje okno wyœwietlania oraz kontekst OpenGL

Display::Display(int width, int height, const std::string& title, Camera* camera)
    : _camera(camera)
{
    _width = width;
    _height = height;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    _glcontext = SDL_GL_CreateContext(_window);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    _isClosed = false;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void Display::SetColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed() { return _isClosed; }

int Display::AxisX() { return currentMouseX; }

int Display::AxisY() { return currentMouseY; }

bool Display::isDragging() { return _isDragging; }

bool Display::isRotating() { return _isRotating; }

void Display::ResetScroolOffset() { _scrollOffset = 0; }

// Detekcja podwójnego klikniêcia
void Display::Update()
{
    SDL_GL_SwapWindow(_window);
    SDL_Event e;
    static Uint32 lastClickTime = 0;
    const Uint32 doubleClickThreshold = 300; // 300ms na podwójne klikniêcie
    static int lastMouseX = -1, lastMouseY = -1;

    while (SDL_PollEvent(&e))
    {
        SDL_GetMouseState(&currentMouseX, &currentMouseY);
        ImGui_ImplSDL2_ProcessEvent(&e);
        _scrollOffset = 0;

        if (e.type == SDL_QUIT)
            _isClosed = true;
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            _width = e.window.data1;
            _height = e.window.data2;
            glViewport(0, 0, _width, _height);
        }
        else if (e.type == SDL_MOUSEWHEEL)
        {
            _scrollOffset = e.wheel.y;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastClickTime < doubleClickThreshold &&
                abs(currentMouseX - lastMouseX) < 5 && abs(currentMouseY - lastMouseY) < 5)
            {
                // Podwójne klikniêcie wykryte!
                glm::vec3 rayDirection = _camera->GetRayFromScreen(currentMouseX, currentMouseY, _width, _height);
                std::cout << "Podwójne klikniêcie! Kierunek promienia: " << rayDirection.x << ", " << rayDirection.y << ", " << rayDirection.z << std::endl;
                // Tu dodamy sprawdzanie kolizji
            }
            lastClickTime = currentTime;
            lastMouseX = currentMouseX;
            lastMouseY = currentMouseY;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
        {
            _isDragging = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
        {
            _isRotating = true;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
        {
            _isRotating = false;
        }
    }
}
