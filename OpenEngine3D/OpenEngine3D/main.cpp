#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "Shader.h""
#include "Rigidbody.h"
#include "Mesh.h"

int main(void) 
{
    Display display(1300,800,"OpenEngine3D");
    Shader shader("./res/basicShader");
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5,-0.5,0)),
        Vertex(glm::vec3(0,0.5,0)),
        Vertex(glm::vec3(0.5,-0.5,0))
     };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    //Rigidbody rigidbody(0.0f, 5.0f, 0.0f);
    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);
        shader.Bind();
        mesh.Draw();

        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
    }
    return 0;
}
