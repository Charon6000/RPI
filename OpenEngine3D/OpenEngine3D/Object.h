#pragma once
#include "Texture.h"
#include "Transform.h"
#include "Shader.h"
#include "Mesh.h"
#include "BoundingSphere.h"
#include <iostream>
#include <string> 

class Object
{

public:
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	Object(std::string nazwa, const std::string& tekstura, Transform transform, const std::string& mesh, const std::string& shader);
	void Update(Camera& camera);
	void SetPosition(glm::vec3 vector);
	void SetRotation(glm::vec3 vector);
	void SetScale(glm::vec3 vector);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	bool CheckCollision(const Object& other);
private:
	Texture _texture;
	Transform _transform;
	Mesh _mesh;
	Shader _shader;
	std::string _nazwa;

	BoundingSphere _boundingSphere;
};

