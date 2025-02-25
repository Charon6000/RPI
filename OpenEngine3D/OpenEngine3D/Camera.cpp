#include "Camera.h"
#include <iostream>

void Camera::updatePosition(glm::vec3 offset) {
    m_position += offset.x * m_right;
    m_position += offset.y * m_up;
    m_position += offset.z * m_forward;
}

void Camera::updateOrientation(float yaw, float pitch) {
    glm::mat4 yawRotation = glm::rotate(glm::radians(yaw), m_up);
    glm::mat4 pitchRotation = glm::rotate(glm::radians(pitch), m_right);

    glm::vec4 newForward = pitchRotation * yawRotation * glm::vec4(m_forward, 0.0f);

    m_forward = glm::normalize(glm::vec3(newForward));
    m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up = glm::normalize(glm::cross(m_right, m_forward));
}

void Camera::zoom(float amount) {
    m_position += m_forward * amount;
}

glm::vec3 Camera::GetRayFromScreen(int mouseX, int mouseY, int screenWidth, int screenHeight) {
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, screenWidth, screenHeight);
    glm::vec3 rayStart = glm::unProject(
        glm::vec3(mouseX, screenHeight - mouseY, 0.0f),
        glm::lookAt(m_position, m_position + m_forward, m_up),
        m_perspective,
        viewport
    );

    glm::vec3 rayEnd = glm::unProject(
        glm::vec3(mouseX, screenHeight - mouseY, 1.0f),
        glm::lookAt(m_position, m_position + m_forward, m_up),
        m_perspective,
        viewport
    );

    glm::vec3 rayDirection = glm::normalize(rayEnd - rayStart);
    return rayDirection;
}
