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
    float color[3] = { 250.0f, 0.0f, 121.0f};

    GameManager GM;
    float rot = 1.0f;
    float vel = 0.001f;
    int x = 5;
    int y = 1;
    int z = -20;
    Camera camera(glm::vec3(x, y, z), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display((float)WIDTH, (float)HEIGHT, "OpenEngine3D");
    Object mcqueenKula("MCQueenKula", "./res/mcqueen.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    Object czarnyKula("CzarnyKula", "./res/suit_guy.jpg", Transform(), "./res/sphere.obj", "./res/basicShader");
    mcqueenKula.SetPosition(glm::vec3(0, 4, 0));
    mcqueenKula.velocity = glm::vec3(0, -0, 0);
    czarnyKula.SetPosition(glm::vec3(0, -4, 0));
    czarnyKula.velocity = glm::vec3(0, 0, 0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(display._window, display._glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool start = true;
    bool isDragging = false;
    int lastMouseX = 0, lastMouseY = 0;
    float sensitivity = 0.1f;

    static float yaw = 90.0f;
    static float pitch = 0.0f;
    

    while (!display.IsClosed())
    {
        int currentMouseX = (display.AxisX() - (WIDTH / 2)), currentMousey = (display.AxisY() - (HEIGHT / 2));
        float scrollOffset = display.GetScrollOffset();

        display.SetColor(color[0], color[1], color[2], 0.0f);
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
        if (ImGui::Button("Start", ImVec2(50, 20))) {
            mcqueenKula.velocity = glm::vec3(0, -0.001, 0);
            czarnyKula.velocity = glm::vec3(0, 0.001, 0);
        }
        ImGui::Text("Tu beda opcje objektow");
        ImGui::Checkbox("Czy jestes gejem?", &dupa);
        ImGui::SliderFloat("Rotacja", &rot, 0.2f, 5.0f);
        ImGui::ColorEdit3("Kolor t³a", color);
        mcqueenKula.SetRotation(glm::vec3(rot, rot, rot));
        
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
       
        if (!ImGui::IsAnyItemActive() && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
            int dx = currentMouseX - lastMouseX;
            int dy = currentMousey - lastMouseY;
            if (display.isDragging()) {
                glm::vec3 offset;
                offset.x = -(dx * 0.1f);
                offset.y = dy * 0.2f;
                offset.z = 0.0f;
                camera.udpatePosition(offset);
            }
            if (display.isRotating()) {
                camera.updateOrientation(-dx * sensitivity, dy * sensitivity);
            }
            if (scrollOffset != 0) {
                camera.zoom(scrollOffset);
                display.ResetScroolOffset();
            }
        }
       
        lastMouseX = currentMouseX;
        lastMouseY = currentMousey;
        display.Update();
        start = false;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}