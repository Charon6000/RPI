#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(const glm::vec3& c, float r): center(c), radius(r){};

BoundingSphere::BoundingSphere(const std::vector<glm::vec3>& vertices) {
	if (vertices.empty()) {
		center = glm::vec3(0);
		radius = 0;
		return;
	}

	glm::vec3 sum(0);
	for (const auto& v : vertices) {
		sum += v;
	}
	center = sum / static_cast<float>(vertices.size());

	radius = 0;

	for (const auto& v : vertices) {
		float distance = glm::length(v - center);
		if (distance > radius) {
			radius = distance;
		}
	}
}