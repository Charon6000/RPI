#include "GameManager.h"

std::vector<Object*> GameManager::obiekty;
void GameManager::Update(Camera& camera)
{
    ObjectCompiling(camera);
    CheckCollisions();
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
    for (size_t i = 0; i < obiekty.size(); i++)
    {
        for (size_t j = i + 1; j < obiekty.size(); j++)
        {
            if (obiekty[i]->CheckCollision(*obiekty[j]))
            {
                std::cout << "Wykryto kolizje: " << obiekty[i]->_nazwa
                    << " i " << obiekty[j]->_nazwa << std::endl;

                obiekty[i]->velocity = -obiekty[i]->velocity;
                obiekty[j]->velocity = -obiekty[j]->velocity;
            }
        }
    }
}