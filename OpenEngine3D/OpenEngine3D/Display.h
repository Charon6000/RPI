#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Camera.h"

class Display
{
public:
	SDL_Window* _window;
	SDL_GLContext _glcontext;

	Display(int width, int height, const std::string& title);
	void SetColor(float r, float g, float b, float a);
	 ~Display();
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
	int _width, _height;
	int z = -20;
	int x = 5;
	int y = 1;

	int currentMouseX, currentMouseY;

	Display(const Display& other) {}
	void operator = (const Display& other) {}
	
	bool _isClosed;
	bool _isDragging = false;
	bool _isRotating = false;
	int _scrollOffset;
	bool _scrolling = false;
};