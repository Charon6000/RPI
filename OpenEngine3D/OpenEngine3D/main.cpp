#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Camera.h"
#include "Object.h"

#define WIDTH 1300
#define HEIGHT 800

int main(void)
{
    Camera camera(glm::vec3(0, 0, -5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display((float)WIDTH, (float)HEIGHT, "OpenEngine3D");
    Object malpa("Malpa", "./res/mcqueen.jpg", Transform(), "./res/monkey3.obj", "./res/basicShader");
    malpa.velocity = glm::vec3(0.001f, 0, 0);
    malpa.SetRotation(glm::vec3(0,3,0));
    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);
        camera.setAspect((float)display.GetWidth() / (float)display.GetHeight());

        malpa.Update(camera);
        display.Update();
    }
    return 0;
}
