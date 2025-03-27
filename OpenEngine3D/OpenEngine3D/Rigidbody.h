#pragma once
#include <cmath> // Dodajemy, aby korzystaæ z funkcji matematycznych
#define M_PI 3.14159265358979323846

class Rigidbody
{
public:
    float x, y, z;
    float velocityX, velocityY, velocityZ;
    float gravity;

    Rigidbody(float posX, float posY, float posZ);

    void Update(float deltaTime);
    void Draw();
};