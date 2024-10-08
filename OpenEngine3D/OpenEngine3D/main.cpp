#define SDL_MAIN_HANDLED
#include <iostream>
#include "Display.h"
#include "Rigidbody.h"
#include <GL/glew.h>

int main(void) 
{
    Display display(800,800,"OpenEngine3D");
    Rigidbody rigidbody(0.0f, 5.0f, 0.0f);
    while (!display.IsClosed())
    {
        display.SetColor(0.0f, 0.4f,0.0f,0.0f);

        rigidbody.Update(0.016f);
        rigidbody.Draw();

        display.Update();
    }
    return 0;
}
