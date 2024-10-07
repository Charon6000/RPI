#pragma once
#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	void SetColor(float r, float g, float b, float a);
	virtual ~Display();
	void Update();
	bool IsClosed();
protected:
private:
	Display(const Display& other) {}
	void operator = (const Display& other) {}

	SDL_Window* _window;
	SDL_GLContext _glcontext;
	bool _isClosed;
};