#include "GameManager.h"

bool GameManager::inercial = true;
std::vector<glm::vec3> GameManager::directions;
float GameManager::GForce;
std::vector<Object*> GameManager::obiekty;
bool GameManager::symulacja = false;
void GameManager::Update(Camera& camera)
{
    ObjectCompiling(camera);
    CheckCollisions();
}

void GameManager::Simulate(bool czy)
{
    symulacja = czy;
    for (int i = 0; i < obiekty.size(); i++)
    {
        if (obiekty[i]->_typ == Kula)
        {
            obiekty[i]->simulate = czy;
        }
    }
}

void GameManager::ObjectCompiling(Camera& camera)
{
    for (int i = 0; i < obiekty.size(); i++)
    {
        obiekty[i]->Update(camera);
    }
}

void GameManager::CheckCollisions()
{   
    if (!symulacja)
        return;
    if (!inercial)
    {
        for (size_t i = 0; i < obiekty.size(); i++)
        {
            for (size_t j = i + 1; j < obiekty.size(); j++)
            {
                float dx = obiekty[i]->GetPosition().x - obiekty[j]->GetPosition().x;
                float dy = obiekty[i]->GetPosition().y - obiekty[j]->GetPosition().y;
                float odleglosc = sqrt(dx * dx + dy * dy);

                if (odleglosc == 0) continue;

                glm::vec3 kierunek(dx / odleglosc, dy / odleglosc, 0);

                float G = 1.0f;
                float sila = (G * obiekty[i]->masa * obiekty[j]->masa) / (odleglosc * odleglosc);

                glm::vec3 przyspieszenie1 = (sila / obiekty[i]->masa) * kierunek;
                glm::vec3 przyspieszenie2 = (sila / obiekty[j]->masa) * -kierunek;

                obiekty[i]->velocity -= przyspieszenie1;
                obiekty[j]->velocity -= przyspieszenie2;
            }
        }

    }


    for (size_t i = 0; i < obiekty.size(); i++)
    {
        for (size_t j = i+1; j < obiekty.size(); j++)
        {

            if (obiekty[i]->CheckCollision(*obiekty[j]))
            {
                std::cout << "Wykryto kolizje: " << obiekty[i]->_nazwa
                    << " i " << obiekty[j]->_nazwa << std::to_string(j) << std::endl;
                if (obiekty[i]->_typ != Static && obiekty[j]->_typ == Static || obiekty[i]->_typ == Static && obiekty[j]->_typ != Static)
                {
                    obiekty[i]->SetPosition(obiekty[i]->GetPosition() - obiekty[i]->velocity);
                    obiekty[i]->velocity.y *= -0.5f;
                    std::cout << obiekty[j]->velocity.y;
                    if (fabs(obiekty[i]->velocity.y) < 0.1f)
                    {
                        obiekty[i]->simulate = false;
                        obiekty[i]->velocity.y = 0.0f;
                    }

                    obiekty[j]->SetPosition(obiekty[j]->GetPosition() - obiekty[j]->velocity);
                    obiekty[j]->velocity.y *= -0.5f;
                    if (obiekty[j]->velocity.y > -0.1f && obiekty[j]->velocity.y < 0.1f)
                    {
                        obiekty[j]->velocity.y = 0.0f;
                        obiekty[j]->simulate = false;
                    }
                }
                else if (obiekty[j]->_typ != Static && obiekty[i]->_typ != Static)
                {
                    if (obiekty[i]->velocity != glm::vec3(0, 0, 0) && obiekty[i]->velocity != glm::vec3(0, 0, 0))
                    {
                        glm::vec3 zmiana = (obiekty[i]->velocity + obiekty[j]->velocity) / glm::vec3(2, 2, 2);
                        obiekty[i]->velocity = zmiana;
                        obiekty[j]->velocity = zmiana;
                    }
                    else
                    {
                        obiekty[i]->velocity = glm::vec3(0, 0, 0);
                        obiekty[i]->simulate = false;
                        obiekty[i]->simulate = false;
                        obiekty[j]->velocity = glm::vec3(0, 0, 0);
                    }
                    
                }
            }
        }
    }
}