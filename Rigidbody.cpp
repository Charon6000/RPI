#include "Rigidbody.h"
#include <GL/glew.h>
#include <cmath>

// Konstruktor
Rigidbody::Rigidbody(float posX, float posY, float posZ)
    : x(posX), y(posY), z(posZ),
    velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f),
    gravity(-9.8f), speedX(0.0f), speedY(0.0f), speedZ(0.0f) {}

// Aktualizacja pozycji
void Rigidbody::Update(float deltaTime) {
    velocityY += gravity * deltaTime;
    x += (velocityX + speedX) * deltaTime;
    y += (velocityY + speedY) * deltaTime;
    z += (velocityZ + speedZ) * deltaTime;

    // Zatrzymujemy obiekt, gdy dotyka ziemi
    if (y < 0) {
        y = 0;
        velocityY = 0;
    }
}

// Rysowanie kuli
void Rigidbody::Draw() {
    float radius = 0.25f; // Promień kuli
    int slices = 32;     // Liczba segmentów (poziomych)
    int stacks = 32;     // Liczba segmentów (pionowych)

    // Ustawiamy macierz modelu
    glPushMatrix();
    glTranslatef(x, y, z);  // Przesunięcie do pozycji ciała sztywnego

    // Rysujemy kulę
    for (int i = 0; i < slices; ++i) {
        float theta1 = (i * M_PI * 2) / slices;
        float theta2 = ((i + 1) * M_PI * 2) / slices;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float phi = (j * M_PI * 2) / stacks;
            float y1 = radius * sin(phi);
            float r1 = radius * cos(phi);

            // Pierwszy wierzchołek
            glVertex3f(r1 * cos(theta1), y1, r1 * sin(theta1));
            // Drugi wierzchołek
            glVertex3f(r1 * cos(theta2), y1, r1 * sin(theta2));
        }
        glEnd();
    }

    glPopMatrix();
}