#define SDL_MAIN_HANDLED
#include <iostream>
#include "Display.h"
#include <GL/glew.h>

int main(void) 
{
    Display display(1300,800,"OpenEngine3D");
    while (!display.IsClosed())
    {
        display.SetColor(0.0f, 0.4f,0.0f,0.0f);
        display.Update();
    }
    return 0;
}
