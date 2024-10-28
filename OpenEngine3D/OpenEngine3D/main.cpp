#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "Shader.h""
#include "Rigidbody.h"
#include "Mesh.h"
#include "Texture.h"

int main(void) 
{
    Display display(1300,800,"OpenEngine3D");
    Shader shader("./res/basicShader");
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-1.0 ,0.0)),
        Vertex(glm::vec3(0,0.5,0), glm::vec2(-0.5, -1.0)),
        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.0, 0.0)), };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Texture texture("./res/mcqueen.jpg");
    //Rigidbody rigidbody(0.0f, 5.0f, 0.0f);
    while (!display.IsClosed())
    {
<<<<<<< HEAD
        display.SetColor(0.6f, 0.0f,0.8f,0.0f);
=======
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);
>>>>>>> origin
        shader.Bind();
        texture.Bind(0);
        mesh.Draw();

        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
    }
    return 0;
}
