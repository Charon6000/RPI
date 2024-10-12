#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "Shader.h""
#include "Rigidbody.h"

int main(void) 
{
    Display display(1300,800,"OpenEngine3D");
    Shader shader("./res/basicShader");

    //Rigidbody rigidbody(0.0f, 5.0f, 0.0f);
    while (!display.IsClosed())
    {
        display.SetColor(0.0f, 0.4f,0.0f,0.0f);
        shader.Bind();
        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
    }
    return 0;
}
