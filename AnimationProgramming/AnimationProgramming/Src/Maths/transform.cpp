#include "Maths/transform.hpp"

#define QUATTOMATRIX

Transform::Transform(const vec3& pos, const Quaternion& rot, const vec3& myScale)
{
	position = pos;
	rotation = rot;
	scale = myScale;
	GetLocalModel();
}

void Transform::SetParent(Transform* futurParent)
{
	parent = futurParent;
}

mat4 Transform::GetLocalModel()
{
	model = M4x4::translate(position) * quaternionToMatrix(rotation) * M4x4::scale(scale);

	return model;
}

mat4 Transform::GetGlobalModel() const
{
	mat4 m = model;

	if (parent != nullptr)
		m = parent->GetGlobalModel() * m;

	return m;
}

vec3 Transform::GetGlobalPosition() const
{
	return M4x4::position(GetGlobalModel());
}

Quaternion Transform::GetGlobalRotation() const
{
	if (parent)
		return quaternionMultiply(parent->GetGlobalRotation(), rotation);

	return rotation;
}


void Transform::Translate(vec3 translation)
{
	position += translation;
}

Transform::~Transform()
{

}