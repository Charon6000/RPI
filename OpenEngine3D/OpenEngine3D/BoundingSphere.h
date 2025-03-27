#pragma once
#include <glm/glm.hpp>
#include <vector>

class BoundingSphere {
public:
    glm::vec3 center;
    float radius;

    BoundingSphere(const glm::vec3& center = glm::vec3(0), float radius = 0);
    BoundingSphere(const std::vector<glm::vec3>& vertices);
};
