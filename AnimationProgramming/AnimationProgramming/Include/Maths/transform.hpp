#pragma once

#include "vec3.hpp"
#include "quaternion.hpp"
#include "mat4.hpp"

#include <vector>

using namespace Maths;

class Transform
{
protected:
public:
	vec3 position = {};
	Quaternion rotation = {0.f, 0.f, 0.f, 1.f};
	vec3 scale = {1.f, 1.f, 1.f};

	mat4 model = M4x4::identity();

	Transform* parent = nullptr;

	Transform() = default;
	Transform(const vec3& pos, const Quaternion& rot, const vec3& myScale);
	~Transform();

	void SetParent(Transform* futurParent);
	void Translate(vec3 translation);

	mat4 GetLocalModel();
	mat4 GetGlobalModel() const;
	vec3 GetGlobalPosition() const;
	Quaternion GetGlobalRotation() const;


};