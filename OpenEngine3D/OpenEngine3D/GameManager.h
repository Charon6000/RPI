#pragma once
#include <vector>
#include "Camera.h"
#include "Object.h"

class Object;

class GameManager {
public:
    static std::vector<Object*> obiekty;
    void Update(Camera& camera);
    void Simulate(bool czy);
private:
    void CheckCollisions();
    void ObjectCompiling(Camera& camera);
};
