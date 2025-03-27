#include "Camera.h"
#include <iostream>

void Camera::udpatePosition(glm::vec3 offset) {

	m_position += offset.x * m_right;
	m_position += offset.y * m_up;
	m_position += offset.z * m_forward;
}

void Camera::updateOrientation(float yaw, float pitch) {
    glm::mat4 yawRotation = glm::rotate(glm::radians(yaw), m_up);  // Obrót wokó³ lokalnej osi Y
    glm::mat4 pitchRotation = glm::rotate(glm::radians(pitch), m_right); // Obrót wokó³ lokalnej osi X

    glm::vec4 newForward = pitchRotation * yawRotation * glm::vec4(m_forward, 0.0f);

    m_forward = glm::normalize(glm::vec3(newForward));
    m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f))); // Aktualizacja prawej osi
    m_up = glm::normalize(glm::cross(m_right, m_forward)); // Aktualizacja górnej osi
}

void Camera::zoom(float amount) {
	m_position += m_forward * amount;
}