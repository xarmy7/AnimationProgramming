#include <iostream>

#include "Maths/vec4.hpp"

using namespace Maths;

float	vec4::index(unsigned int index) const
{
	// return a copy of coordinate with an index btw 0-3
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default: return 0.f;
	}
}


std::ostream& operator<<(std::ostream& o, vec4 v)
{
	return o << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
}

float   vec4::squareLength() const
{
	return x * x + y * y + z * z + w * w;
}

float   vec4::length() const
{
	return sqrtf(squareLength());
}

float& vec4::operator[](unsigned int index)
{
	// Avoid segfault
	if (index >= 4) index = index % 4;
	return *(&x + index);
}

void vec4::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;
}

vec4 vec4::operator*(const float f) const
{
	return { x * f, y * f, z * f, w * f };
}

vec4 vec4::operator-() const
{
	return { -x, -y, -z, -w };
}

vec4  vec4::normalize() const
{
	float l = length();
	if (l == 0.f) return vec4();

	return { x / l, y / l, z / l, w / l };
}