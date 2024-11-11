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
    Display display(WIDTH, HEIGHT, "OpenEngine3D");
    Shader shader("./res/basicShader");
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-1.0 ,0.0)),
        Vertex(glm::vec3(0,0.5,0), glm::vec2(-0.5, -1.0)),
        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.0, 0.0)), };

	unsigned int indices[] = { 0, 1, 2 };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh2("./res/monkey3.obj");
    Texture texture("./res/mcqueen.jpg");
    //Rigidbody rigidbody(0.0f, 5.0f, 0.0f);
    Camera camera(glm::vec3(0, 0, -5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);


		transform.GetPos().x = sinf(counter);
        transform.GetRot().z = cosf(counter);
        transform.GetRot().x = counter * 500;
        transform.GetRot().y = counter * 500;
        transform.GetRot().z = counter * 500;
		transform.SetScale(glm::vec3(cosCounter,cosCounter,cosCounter));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        mesh2.Draw();

        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
		counter += 0.00001f;
    }
    return 0;
}
