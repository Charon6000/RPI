#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Camera.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);
	void SetColor(float r, float g, float b, float a);
	 ~Display();
	void Update();
	bool IsClosed();

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
protected:
private:
	int _width, _height;

	Display(const Display& other) {}
	void operator = (const Display& other) {}

	SDL_Window* _window;
	SDL_GLContext _glcontext;
	bool _isClosed;
};