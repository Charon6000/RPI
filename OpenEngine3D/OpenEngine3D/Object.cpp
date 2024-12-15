#include "Object.h"
#include "BoundingSphere.h"

Object::Object(std::string nazwa, const std::string& tekstura, Transform transform, const std::string& mesh, const std::string& shader)
	:_texture(tekstura), _transform(transform), _mesh(mesh), _shader(shader), _nazwa(nazwa)
{
	this->_nazwa = nazwa;
	std::cout << "Stworzono obiekt: " << nazwa << std::endl;

	_boundingSphere = BoundingSphere(_mesh.GetVertices());
}

void Object::Update(Camera& camera)
{
	//kompilacja calego objektu
	_shader.Bind();
	_texture.Bind(0);
	_shader.Update(_transform, camera);
	_mesh.Draw();

	//ruch ze sta�� pr�dko�ci�
	SetPosition(GetPosition() + velocity);

	_boundingSphere.center = GetPosition();
}

void Object::SetPosition(glm::vec3 vector)
{
	_transform.SetPos(vector);
}
void Object::SetRotation(glm::vec3 vector)
{
	_transform.SetRot(vector);
}
void Object::SetScale(glm::vec3 vector)
{
	_transform.SetScale(vector);
}

glm::vec3 Object::GetPosition()
{
	return _transform.GetPos();
}

glm::vec3 Object::GetRotation()
{
	return _transform.GetRot();
}

glm::vec3 Object::GetScale()
{
	return _transform.GetScale();
}

bool Object::CheckCollision(const Object& other)
{
	float distance = glm::abs(glm::length(_boundingSphere.center - other._boundingSphere.center));
	float combinedRadius = _boundingSphere.radius + other._boundingSphere.radius;
	if (distance <= combinedRadius) {
		return true;
	}
	return false;
}
