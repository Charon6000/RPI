#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

# include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	glm::mat4 m_perspective;
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0,0,1);
		m_up = glm::vec3(0, 1, 0);
		this->fov = fov;
		this->aspect = aspect;
		this->zNear = zNear;
		this->zFar = zFar;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void setAspect(float aspect)
	{
		this->aspect = aspect;
		m_perspective = glm::perspective(this->fov, this->aspect, this->zNear, this->zFar);
	}

protected:
private:
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	float fov, aspect, zNear, zFar;

};

#endif //CAMERA_H_INCLUDED