#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Camera.h"

class Display
{
public:
    SDL_Window* _window;
    SDL_GLContext _glcontext;

    Display(int width, int height, const std::string& title, Camera* camera);
    void CheckRayCollisions(const glm::vec3& rayOrigin, const glm::vec3& rayDirection);
    void SetColor(float r, float g, float b, float a);
    void Update();
    bool IsClosed();
    void ResetScroolOffset();
    int Zoom();
    int AxisX();
    int AxisY();
    bool isDragging();
    bool isRotating();

    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    int GetScrollOffset() { return _scrollOffset; }

protected:
private:
    Camera* _camera;
    int _width, _height;
    int z = -20;
    int x = 5;
    int y = 1;

    int currentMouseX, currentMouseY;

    // Zmienne do obs³ugi podwójnego klikniêcia
    float firstClickTime = 0.0f;  // Czas pierwszego klikniêcia
    bool isDoubleClick = false;    // Flaga podwójnego klikniêcia
    int firstClickX = 0, firstClickY = 0; // Pozycja pierwszego klikniêcia

    Display(const Display& other) {}
    void operator = (const Display& other) {}

    bool _isClosed;
    bool _isDragging = false;
    bool _isRotating = false;
    int _scrollOffset;
    bool _scrolling = false;

};
