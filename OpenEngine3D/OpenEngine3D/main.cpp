#define SDL_MAIN_HANDLED
#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h""
#include "Rigidbody.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

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
	Transform transform;

	float counter = 0.0f;

    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f,121.0f,0.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);


		transform.GetPos().x = sinf(counter);
        transform.GetRot().z = counter *50;
		transform.SetScale(glm::vec3(cosCounter,cosCounter,cosCounter));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform);
        mesh.Draw();

        //rigidbody.Update(0.006f);
        //rigidbody.Draw();

        display.Update();
		counter += 0.01f;
    }
    return 0;
}
