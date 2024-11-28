#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Rigidbody.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1300
#define HEIGHT 800

int main(void)
{
    Camera camera(glm::vec3(0, 0, -5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display(WIDTH, HEIGHT, "OpenEngine3D");
    Shader shader("./res/basicShader");
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-1.0 ,0.0)),
        Vertex(glm::vec3(0,0.5,0), glm::vec2(-0.5, -1.0)),
        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.0, 0.0)), };

	unsigned int indices[] = { 0, 1, 2 };

    //Mesh mesh("./res/mcQueen_a.obj");
    Mesh mesh2("./res/monkey3.obj");
    Texture texture("./res/mcqueen.jpg");

	Transform transform;

	float counter = 0.0f;

    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);

        camera.setAspect((float)display.GetWidth() / (float)display.GetHeight());

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

        transform.SetPos(glm::vec3(sinCounter, sinCounter, sinCounter));
        transform.SetRot(glm::vec3(cosCounter, cosCounter, cosCounter));
		transform.SetScale(glm::vec3(cosCounter,cosCounter,cosCounter));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        //mesh.Draw();
        mesh2.Draw();

        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
		counter += 0.0001f;
    }
    return 0;
}
