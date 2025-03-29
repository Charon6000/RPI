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
    float color[3] = { 250.0f, 0.0f, 121.0f};
    GameManager GM;
    int x = 5;
    int y = 1;
    int z = -20;
    Camera camera(glm::vec3(x, y, z), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Display display((float)WIDTH, (float)HEIGHT, "OpenEngine3D");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(display._window, display._glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool start = false;
    bool isDragging = false;
    int lastMouseX = 0, lastMouseY = 0;
    float sensitivity = 0.1f;

    int objectCounter = 0;




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
        ImGui::ColorEdit3("Kolor t³a", color);
        if (ImGui::Button("Start", ImVec2(0, 20))) {
            GameManager::inercial = false;
            if (GameManager::obiekty.size() > 0)
            {
                for (int i = 0; i < GameManager::obiekty.size(); i++)
                {
                    if (GameManager::obiekty[i]->_typ == Static)
                        GameManager::inercial = true;
                }
            }
            GM.Simulate(true);
        }
        if (ImGui::Button("Stop", ImVec2(0, 20))) {
            GM.Simulate(false);
        }

        static char str0[128] = "";
        ImGui::InputTextWithHint("Podaj nazwe","Nazwa", str0, IM_ARRAYSIZE(str0));

        const char* items[] = {"Kwadrat", " Kula", "Malpa", "Wlasne"};
        static int item_current = 1;
        ImGui::ListBox("Wybierz rodzaj", &item_current, items, IM_ARRAYSIZE(items), 4);

        static bool statyczny = false;
        ImGui::Checkbox("Czy statyczny?", &statyczny);

        if (ImGui::Button("Dodaj objekt", ImVec2(100, 0))) {
            switch (item_current)
            {
            case 0:
                if (statyczny)
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/cube.obj", "./res/basicShader", Static);
                else
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/cube.obj", "./res/basicShader", Kwadrat);
                break;
            case 1:
                if (statyczny)
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/sphere.obj", "./res/basicShader", Static);
                else
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/sphere.obj", "./res/basicShader", Kula);
                break;
            case 2:
                if (statyczny)
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/monkey3.obj", "./res/basicShader", Static);
                else
                    new Object(str0, "./res/suit_guy.jpg", Transform(), "./res/monkey3.obj", "./res/basicShader", Kula);
                break;
            case 3:
                break;
            default:
                break;
            }
            
            objectCounter++;
        }

        ImGui::Text("Opcje objektow");
        for (size_t i = 0; i < objectCounter; ++i) {
            std::string& nazwa = GM.obiekty[i]->_nazwa;
            char buf[128];

            strncpy_s(buf, sizeof(buf), nazwa.c_str(), sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = '\0';

            if (ImGui::CollapsingHeader(nazwa.c_str()))
            {
                
                ImGui::SeparatorText("Kontrolki");
                glm::vec3 position = GM.obiekty[i]->GetPosition();
                glm::vec3 skala = GM.obiekty[i]->GetScale();
                glm::vec3 rotacja = GM.obiekty[i]->GetRotation();

                if (ImGui::InputFloat3("Pozycja", &position[0])) {
                    GM.obiekty[i]->SetPosition(position);
                }
                if (ImGui::InputFloat3("Rotacja", &rotacja[0])) {
                    GM.obiekty[i]->SetRotation(rotacja);
                }
                if (ImGui::InputFloat3("Skala", &skala[0])) {
                    GM.obiekty[i]->SetScale(skala);
                }
                ImGui::SeparatorText("Szybkoœci");
                glm::vec3 predkosc = GM.obiekty[i]->velocity;
                glm::vec3 acc = GM.obiekty[i]->acceleration;
                bool symuluj = GM.obiekty[i]->simulate;

                if (ImGui::InputFloat3("Predkosc", &predkosc[0])) {
                    GM.obiekty[i]->velocity = predkosc;
                }
                if (ImGui::InputFloat3("Przyspieszenie", &acc[0])) {
                    GM.obiekty[i]->acceleration = acc;
                }
                float mas = GM.obiekty[i]->masa;
                ImGui::InputFloat("Masa", &mas);
                    try{
                        GM.obiekty[i]->masa = mas;
                    }
                    catch (...)
                    {
                        continue;
                    }

                if (ImGui::Checkbox("Symuluj", &symuluj)) {
                    GM.obiekty[i]->simulate = symuluj;
                }
            }
        }
        
        
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
                camera.updateOrientation(-dx * sensitivity, -dy * sensitivity);
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