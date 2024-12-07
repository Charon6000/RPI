#include "Display.h"
#include <iostream>
#include<GL/glew.h>
#include "Camera.h"

Display::Display(int width, int height, const std::string& title)
	: _width(width), _height(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
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

Display::~Display()
{
	SDL_GL_DeleteContext(_glcontext);
	SDL_DestroyWindow(_window);
	SDL_Quit();

}

void Display::SetColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed()
{
	return _isClosed;
}

void Display::Update()
{
	SDL_GL_SwapWindow(_window);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			_isClosed = true;
		else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
			_width = e.window.data1;
			_height = e.window.data2;
			glViewport(0, 0, _width, _height);
		}
	}
}