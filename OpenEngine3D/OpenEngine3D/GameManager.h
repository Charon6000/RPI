#pragma once
#include <vector>
#include "Camera.h"
#include "Object.h"

class Object;

class GameManager {
public:
    static bool symulacja;
    static bool inercial;
    static float GForce;
    static std::vector<glm::vec3> directions;
    static std::vector<Object*> obiekty;
    void Update(Camera& camera);
    void Simulate(bool czy);
private:
    void CheckCollisions();
    void ObjectCompiling(Camera& camera);
};
