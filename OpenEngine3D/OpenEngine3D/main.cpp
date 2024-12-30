#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Camera.h"
#include "Object.h"
#include "GameManager.h"

#define WIDTH 1300
#define HEIGHT 800

int main(void)
{
    GameManager GM;
    Camera camera(glm::vec3(0, 0, -10), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display((float)WIDTH, (float)HEIGHT, "OpenEngine3D");
    Object mcqueenKula("MCQueenKula", "./res/mcqueen.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    Object czarnyKula("CzarnyKula", "./res/suit_guy.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    mcqueenKula.SetPosition(glm::vec3(0, 4, 0));
    mcqueenKula.velocity = glm::vec3(0, -0.01f, 0);
    czarnyKula.SetPosition(glm::vec3(0, -4, 0));
    czarnyKula.velocity = glm::vec3(0, 0.01f, 0);
    GameManager::obiekty.push_back(&mcqueenKula);
    GameManager::obiekty.push_back(&czarnyKula);
    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f, 121.0f, 0.0f);
        camera.setAspect((float)display.GetWidth() / (float)display.GetHeight());

        GM.Update(camera);
        display.Update();
    }
    return 0;
}