#pragma once

#include "mat4.hpp" // include vec3 && vec4 too

namespace Maths
{
	struct cylinder;
	struct referential3;

	using Quaternion = vec4;

	// Returns the identity quaternion.
	inline Quaternion	quaternionIdentity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); };
	inline Quaternion	quaternionMultiply(const Quaternion& q1, const Quaternion& q2)
	{
		// (ix1 + jy1 + kz1 + w1) * (ix2 + jy2 + kz2 + w2)
		return {
			q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
		   -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
			q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
		   -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w
		};
	}
	inline float		quaternionLength(const Quaternion& q) {
		return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	}
	inline Quaternion	quaternionNormalize(const Quaternion& q) {
		float l = q.length();
		if (l == 0.f) return Quaternion();

		return { q.x / l, q.y / l, q.z / l, q.w / l };
	}


	Quaternion quaternionConjugate(const Quaternion& q);
	Quaternion quaternionInverse(const Quaternion& q);
	// Returns quaternion based on the rotation from one vector to another.
	Quaternion quaternionFromVectors(const vec3& from, const vec3& to);
	/// Returns a quaternion equivalent to a rotation around an axis.
	Quaternion quaternionFromAxisAngle(const vec3& axis, float angle);
	/// Return an axis and an angle equivalent to the quaternion
	void quaternionToAxisAngle(const Quaternion& q, vec3& axis, float& angle);
	/// Returns a quaternion equivalent to Euler angles.
	Quaternion quaternionFromEulerAngles(float rall, float pitch, float yaw);
	Quaternion quaternionFromEulerAngles(const vec3& radAngles);
	// Returns a couple of euler angles from quat, in Radians
	vec3 quaternionToEulerAngles(const Quaternion& q);
	// Returns a new `vec3` with components rotated by Quaternion `q`.
	vec3 vectorRotateByQuaternion(const vec3& vector, const Quaternion& q);

	mat4 quaternionToMatrix(const Quaternion& quat);

	// Primitive & Quaternion 
	vec3			getNormalFromQuaternion(const Quaternion& yAxisQuaternion);
	Quaternion		getQuaternionFromNormal(const vec3& normal);
}