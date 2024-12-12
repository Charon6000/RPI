#include "Object.h"

Object::Object(std::string nazwa, const std::string& tekstura, Transform transform, const std::string& mesh, const std::string& shader)
	:_texture(tekstura), _transform(transform), _mesh(mesh), _shader(shader)
{
	this->_nazwa = nazwa;
	std::cout << "Stworzono obiekt: " << nazwa << std::endl;
}

void Object::Update(Camera& camera)
{
	//kompilacja calego objektu
	_shader.Bind();
	_texture.Bind(0);
	_shader.Update(_transform, camera);
	_mesh.Draw();

	//ruch ze sta³¹ prêdkoœci¹
	SetPosition(GetPosition() + velocity);
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