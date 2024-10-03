#include "Rigidbody.h"

Rigidbody::Rigidbody(float posX, float posY, float posZ)
    : x(posX), y(posY), z(posZ),
    velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f),
    gravity(-9.8f) {}

void Rigidbody::Update(float deltaTime) {
    velocityY += gravity * deltaTime;

    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
    z += velocityZ * deltaTime;

    if (y < 0) {
        y = 0;
        velocityY = 0;
    }
}

void Rigidbody::Draw() {
    glPushMatrix();
    glTranslatef(x, y, z);

    int slices = 32; // liczba poziomych segmentów
    int stacks = 32; // liczba pionowych segmentów
    float radius = 0.5f;

    for (int i = 0; i < slices; ++i) {
        float theta1 = (i * M_PI * 2) / slices;     // k¹t w radianach
        float theta2 = ((i + 1) * M_PI * 2) / slices; // nastêpny k¹t

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float phi = (j * M_PI) / stacks; // k¹t w pionie
            float y1 = radius * sin(phi);
            float r1 = radius * cos(phi);

            // Pierwszy wierzcho³ek
            glVertex3f(r1 * cos(theta1), y1, r1 * sin(theta1));
            // Drugi wierzcho³ek
            glVertex3f(r1 * cos(theta2), y1, r1 * sin(theta2));
        }
        glEnd();
    }

    // Dodajemy rysowanie dolnej czêœci kuli
    for (int i = 0; i < slices; ++i) {
        float theta1 = (i * M_PI * 2) / slices;
        float theta2 = ((i + 1) * M_PI * 2) / slices;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float phi = (j * M_PI) / stacks;
            float y1 = radius * sin(phi);
            float r1 = radius * cos(phi);

            // Pierwszy wierzcho³ek dla dolnej czêœci
            glVertex3f(r1 * cos(theta1), -y1, r1 * sin(theta1));
            // Drugi wierzcho³ek dla dolnej czêœci
            glVertex3f(r1 * cos(theta2), -y1, r1 * sin(theta2));
        }
        glEnd();
    }

    glPopMatrix();
}
