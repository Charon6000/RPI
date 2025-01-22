#include "Camera.h"
#include <iostream>

void Camera::OnMouseAction(glm::vec3 vector) {
	m_position = vector;
}