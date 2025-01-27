#include "Camera.h"
#include <iostream>

void Camera::udpatePosition(glm::vec3 pos) {
	m_position = pos;
}

void Camera::updateOrientation(float yaw, float pitch) {
	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_forward = glm::normalize(front);

	glm::vec3 right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_up = glm::normalize(glm::cross(right, m_forward));
}
