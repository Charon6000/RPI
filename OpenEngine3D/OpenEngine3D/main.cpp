#define SDL_MAIN_HANDLED
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include "Display.h"
#include "Camera.h"
#include "Object.h"
#include "GameManager.h"

#define WIDTH 1300
#define HEIGHT 800

int main(void)
{
    //testowa
    bool dupa = true;

    GameManager GM;
    float rot = 1.0f;
    Camera camera(glm::vec3(0, 0, -10), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display((float)WIDTH, (float)HEIGHT, "OpenEngine3D");
    Object mcqueenKula("MCQueenKula", "./res/mcqueen.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    Object czarnyKula("CzarnyKula", "./res/suit_guy.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    mcqueenKula.SetPosition(glm::vec3(0, 4, 0));
    mcqueenKula.velocity = glm::vec3(0, -0.01f, 0);
    czarnyKula.SetPosition(glm::vec3(0, -4, 0));
    czarnyKula.velocity = glm::vec3(0, 0.01f, 0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(display._window, display._glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool start = true;
    while (!display.IsClosed())
    {
        display.SetColor(250.0f, 0.0f, 121.0f, 0.0f);
        camera.setAspect((float)display.GetWidth() / (float)display.GetHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        GM.Update(camera);

        if (start)
        {
            ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.2f, io.DisplaySize.y), ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        }
        
        //testowe
        ImGui::Begin("Opcje!!!");
        ImGui::Text("Tu beda opcje objektow");
        ImGui::Checkbox("Czy jestes gejem?", &dupa);
        ImGui::SliderFloat("Rotacja", &rot, 0.2f, 5.0f);
        mcqueenKula.SetRotation(glm::vec3(rot, rot, rot));
        
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        display.Update();
        start = false;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}