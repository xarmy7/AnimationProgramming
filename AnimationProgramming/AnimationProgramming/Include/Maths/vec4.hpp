#pragma once

#include "vec3.hpp"

namespace Maths
{
	class vec4
	{
	private:

	public:
		float x, y, z, w;
		vec4() :x(0.f), y(0.f), z(0.f), w(0.f) {}
		vec4(float all) :x(all), y(all), z(all), w(all) {}
		vec4(float _x, float _y, float _z, float _w)
			:x(_x), y(_y), z(_z), w(_w) {}
		vec4(float* coords) :x(coords[0]), y(coords[1]), z(coords[2]), w(coords[3]) {};
		vec4(vec3 v, float w) :x(v.x), y(v.y), z(v.z), w(w) {}

		float& operator[](unsigned int index);
		void operator/=(const float f);
		vec4 operator*(const float f) const;
		vec4 operator-() const;

		float	index(unsigned int index) const;

		float   length() const;
		float   squareLength() const;
		vec4  normalize() const;
	};
}

std::ostream& operator<<(std::ostream& o, Maths::vec4 v);