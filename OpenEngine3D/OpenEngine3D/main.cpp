#include <GLFW/glfw3.h> // GLFW
#include "Rigidbody.h"
#define M_PI 3.14159265358979323846

// Ustawienie perspektywy
void SetPerspective() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = 1920.0f / 1080.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float fov = 45.0f;

    // Obliczanie warto�ci do matrycy perspektywicznej
    float top = nearPlane * tan(fov * 0.5f * (M_PI / 180.0f));
    float right = top * aspectRatio;

    glFrustum(-right, right, -top, top, nearPlane, farPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Ustawienie pozycji kamery
    glTranslatef(0.0f, -1.0f, -5.0f); // Pozycja kamery
}

int main(void) {
    GLFWwindow* window;

    /* Inicjalizacja biblioteki */
    if (!glfwInit())
        return -1;

    /* Tworzenie okna oraz kontekstu OpenGL */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Ustawienie kontekstu okna jako bie��cego */
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST); // W��czenie testowania g��boko�ci
    SetPerspective(); // Ustawienie kamery perspektywistycznej

    Rigidbody rigidbody(0.0f, 1.0f, 0.0f);  // Inicjalizowanie obiektu z pozycj� pocz�tkow�

    /* P�tla g��wna a� do zamkni�cia okna */
    while (!glfwWindowShouldClose(window)) {
        /* Renderowanie */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float deltaTime = 0.016f; // Aktualizacja obiektu, czas na klatk� (czyli 60 fps)
        rigidbody.Update(deltaTime);

        rigidbody.Draw(); // Rysowanie obiektu

        /* Zamiana bufor�w frontowych i tylnych */
        glfwSwapBuffers(window);

        /* Sprawdzenie i przetworzenie zdarze� */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
