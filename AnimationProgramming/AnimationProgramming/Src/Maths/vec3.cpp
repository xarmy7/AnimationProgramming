
#include <cmath>

#include "Maths/vec2.hpp"
#include "Maths/vec3.hpp"
#include "Maths/vec4.hpp"

using namespace Maths;

vec3   vec3::zero = { 0.f, 0.f, 0.f };

vec3   vec3::right = { 1.f, 0.f, 0.f };
vec3   vec3::left = { -1.f, 0.f, 0.f };
vec3   vec3::up = { 0.f, 1.f, 0.f };
vec3   vec3::down = { 0.f, -1.f, 0.f };
vec3   vec3::forward = { 0.f, 0.f, 1.f };
vec3   vec3::backward = { 0.f, 0.f, -1.f };


vec3::vec3()
    :x(0.f), y(0.f), z(0.f)
{}

vec3::vec3(float equal)
    : x(equal), y(equal), z(equal)
{}

vec3::vec3(float _x, float _y, float _z)
 :x(_x), y(_y), z(_z)
{}

vec3::vec3(const vec3& f)
    :x(f.x), y(f.y), z(f.z)
{}

vec3::vec3(const vec2& v2)
    : x(v2.x), y (v2.y), z(0.f)
{}

vec3::vec3(const vec4& v4)
    : x(v4.x), y(v4.y), z(v4.z)
{}

////////////////////////////// OPERATOR //////////////////////////////


vec3::operator float* ()
{
    return &x;
}


vec3& vec3::operator=(const vec3& f)
{
    x = f.x;
    y = f.y;
    z = f.z;
    return *this;
}

bool vec3::operator==(const vec3& f)
{
    return ((f.x - x) <= (float)1E-54 && (f.y - y) <= (float)1E-54 && (f.z - z) <= (float)1E-54);
}


vec3  vec3::operator-() const
{
    return { -x, -y, -z };
}

void    vec3::operator+=(const vec3& f)
{
    x += f.x;
    y += f.y;
    z += f.z;
}

vec3  vec3::operator+(const vec3& f)
{
    return { x + f.x, y + f.y, z + f.z };
}

vec3  vec3::operator+(const float& f) const
{
    return { x + f, y + f, z + f };
}

void    vec3::operator-=(const vec3& f)
{
    *this += -f;
}

vec3  vec3::operator-(const vec3& f)
{
    return { x - f.x, y - f.y, z - f.z };
}

void    vec3::operator*=(const vec3& f)
{
    x *= f.x;
    y *= f.y;
    z *= f.z;
}

vec3    vec3::operator*(const float f)
{
    return { x * f, y * f, z * f };
}

vec3    Maths::operator*(const vec3& f1, const float f)
{
    return { f1.x * f, f1.y * f, f1.z * f };
}

vec3  vec3::operator*(const vec3 f) const
{
    return { x * f.x, y * f.y, z * f.z };
}

vec3  Maths::operator*(float f, vec3 v)
{
    return v * f;
}

vec3    vec3::operator/(const float f)
{
    if (f != 0)
        return { x / f, y / f, z / f };
    else
        return { 0.f, 0.f, 0.f };
}

vec3  vec3::operator^(const vec3 f)
{
    return cross(*this, f);
}

float   vec3::operator[](const int index) const
{
    return *(&x + index%3);
}

vec3    Maths::operator-(const vec3& f1, const vec3& f2)
{
    return {f1.x - f2.x, f1.y - f2.y, f1.z - f2.z};
}
vec3    Maths::operator+(const vec3& f1, const vec3& f2)
{
    return { f1.x + f2.x, f1.y + f2.y, f1.z + f2.z };
}

std::ostream& Maths::operator<<(std::ostream& o, vec3 f)
{
    return o << "x : " << f.x << ", y : " << f.y << ", z : " << f.z;
}

////////////////////////////// VECTOR OPERATION //////////////////////////////

float   Maths::dot(vec3 v1, vec3 v2)
{
    return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

vec3    Maths::cross(const vec3& v1, const vec3& v2)
{
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

float   vec3::length() const
{
    return sqrtf(squareLength());
}

float   vec3::squareLength() const
{
    return x * x + y * y + z * z;
}

vec3    vec3::normalize() const
{
    float l = length();
    if (l == 0.f) return vec3();

    return { x / l, y / l, z / l };
}

vec3    vec3::negate() const
{
    return { -x, -y, -z };
}

vec3    vec3::reflect(const vec3& normal)
{
    return *this - 2.f * dot(*this, normal) * normal;
}

bool    vec3::equals(const vec3& toComapre) const
{
    return (fabsf(x - toComapre.x) <= 0.001f && fabsf(y - toComapre.y) <= 0.001f && fabsf(z - toComapre.z) <= 0.001f);
}

float   Maths::angle(vec3 v1, vec3 v2)
{
    float   normsProduct = (v1.length() * v2.length());
    if (normsProduct == 0.f)
        return 0.f;

    float   dotProd = dot(v1, v2);
    return fabsf(dotProd) < normsProduct ? acosf(dotProd / normsProduct) : 0.f;
}

////////////////////////////// EXTERNALS //////////////////////////////
