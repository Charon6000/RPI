#include "Rigidbody.h"
#include <GL/glew.h>
#include <cmath>

// Konstruktor: Inicjalizuje pozycję i ustawienia początkowe Rigidbody
Rigidbody::Rigidbody(float posX, float posY, float posZ)
    : x(posX), y(posY), z(posZ),
    velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f),
    gravity(-9.8f) {} // Domyślna wartość przyspieszenia grawitacyjnego

// Update: Aktualizuje pozycję i prędkość Rigidbody na podstawie upływu czasu
void Rigidbody::Update(float deltaTime) {
    // Zmienia prędkość pionową pod wpływem grawitacji
    velocityY += gravity * deltaTime;

    // Aktualizuje pozycję na podstawie prędkości i czasu
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
    z += velocityZ * deltaTime;

    // Sprawdza, czy obiekt dotknął ziemi, i zatrzymuje jego ruch w pionie
    if (y < 0) {
        y = 0;           // Ustawia pozycję na poziomie ziemi
        velocityY = 0;   // Resetuje prędkość pionową
    }
}

// Draw: Renderuje kulę reprezentującą Rigidbody
void Rigidbody::Draw() {
    float radius = 0.25f; // Promień kuli
    int slices = 32;     // Liczba segmentów (poziomych)
    int stacks = 32;     // Liczba segmentów (pionowych)

    // Ustawia macierz modelu, aby przesunąć kulę do pozycji Rigidbody
    glPushMatrix();
    glTranslatef(x, y, z);  // Przesunięcie do aktualnej pozycji

    // Rysuje kulę za pomocą GL_TRIANGLE_STRIP
    for (int i = 0; i < slices; ++i) {
        float theta1 = (i * M_PI * 2) / slices;       // Kąt początkowy segmentu
        float theta2 = ((i + 1) * M_PI * 2) / slices; // Kąt końcowy segmentu

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float phi = (j * M_PI * 2) / stacks;  // Kąt pionowy segmentu
            float y1 = radius * sin(phi);        // Pozycja Y na powierzchni kuli
            float r1 = radius * cos(phi);        // Promień koła poziomego

            // Pierwszy wierzchołek segmentu
            glVertex3f(r1 * cos(theta1), y1, r1 * sin(theta1));
            // Drugi wierzchołek segmentu
            glVertex3f(r1 * cos(theta2), y1, r1 * sin(theta2));
        }
        glEnd();
    }

    // Przywraca poprzednią macierz modelu
    glPopMatrix();
}
