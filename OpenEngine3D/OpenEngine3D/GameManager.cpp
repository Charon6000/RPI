#include "GameManager.h"

std::vector<Object*> GameManager::obiekty;
void GameManager::Update(Camera& camera)
{
    ObjectCompiling(camera);
    CheckCollisions();
}

void GameManager::Simulate(bool czy)
{
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
    for (size_t i = 0; i < obiekty.size(); i++)
    {
        for (size_t j = i+1; j < obiekty.size(); j++)
        {

            if (obiekty[i]->CheckCollision(*obiekty[j]))
            {
                std::cout << "Wykryto kolizje: " << obiekty[i]->_nazwa
                    << " i " << obiekty[j]->_nazwa<< std::to_string(j) << std::endl;
                if (obiekty[i]->_typ != Static)
                {
                    obiekty[i]->SetPosition(obiekty[i]->GetPosition() - obiekty[i]->velocity);
                    obiekty[i]->velocity.y *= -0.5f;
                    std::cout << obiekty[j]->velocity.y;
                    if (fabs(obiekty[i]->velocity.y) < 0.00005f)
                    {
                        obiekty[i]->simulate = false;
                        obiekty[i]->velocity.y = 0.0f;
                    }
                }
                
                if (obiekty[j]->_typ != Static)
                {
                    obiekty[j]->SetPosition(obiekty[j]->GetPosition() - obiekty[j]->velocity);
                    obiekty[j]->velocity.y *= -0.5f;
                    if (obiekty[j]->velocity.y > -0.1f && obiekty[j]->velocity.y < 0.1f)
                    {
                        obiekty[j]->velocity.y = 0.0f;
                        obiekty[j]->simulate = false;
                    }
                }
            }
        }
    }
}