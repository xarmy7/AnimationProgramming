
#include <cmath>

#include "Maths/maths.hpp"

using namespace Maths;

vec2   vec2::i = {1.f, 0.f};
vec2   vec2::j = {0.f, 1.f};


vec2::vec2()
:x(0.f), y(0.f)
{}


vec2::vec2(float _x, float _y)
//:x(_x), y(_y), z(_z)
{
    x = _x;
    y = _y;
}

vec2::vec2(const vec2& f)
:x(f.x), y(f.y)
{}

vec2::operator float*()
{
    return &x;  
}


vec2& vec2::operator=(const vec2& f)
{
    x = f.x; 
    y = f.y;
    return *this;
}

bool vec2::operator==(const vec2& f)
{
    return ((f.x - x) <= (float)1E-54 && (f.y - y) <= (float)1E-54);
}


vec2  vec2::operator-() const
{
    vec2 f = {-x, -y};
    return f;
}

void vec2::operator-()
{
    x = -x;
    y = -y;
}

void    vec2::operator+=(const vec2& f)
{
    x += f.x;
    y += f.y;
}

vec2  vec2::operator+(const vec2& f)
{
    return { x + f.x, y + f.y };
}


void    vec2::operator-=(const vec2& f)
{
    *this += -f;
}

vec2    vec2::operator-(const vec2& f)
{
    return { x - f.x, y - f.y };
}

vec2    Maths::operator-(const vec2& f1, const vec2& f2)
{
    return { f1.x - f2.x, f1.y - f2.y };
}

void    vec2::operator*=(const vec2& f)
{
    x *= f.x;
    y *= f.y;
}

vec2    vec2::operator*(const float f)
{
    return {x * f, y * f};
}

vec2  vec2::operator*(const vec2 f)
{
    return { x * f.x, y * f.y };
}

vec2    vec2::operator/(const float f)
{
    if (f != 0)
        return { x / f, y / f };
    else
        return { 0.f, 0.f };
}


float   vec2::operator[](const int index) const
{
    return *(&x + index);
}

float   Maths::dot2(const vec2& v1, const vec2& v2)
{
    return { v1.x * v2.x + v1.y * v2.y };
}

float   Maths::angle2(const vec2& v1, const vec2& v2)
{
    float   normsProduct = (v1.length() * v2.length());
    if (normsProduct == 0.f)
        return 0.f;

    float   dotProd = dot2(v1, v2);
    return fabsf(dotProd) < normsProduct ? acosf(dotProd / normsProduct) : 0.f;
}


float   vec2::length() const
{
    return sqrtf(dot2(*this, *this));
}

float   vec2::squareLength() const
{
    return x * x + y * y;
}


vec2  vec2::normalize() const
{
    float l = length();
    return { x / l, y / l };
}

vec2  vec2::getRotated(float angleDeg) const
{
    angleDeg = angleDeg * DEGTORAD;

    float c = cosf(angleDeg), s = sinf(angleDeg);

    return { x * c - y * s ,
             x * s + y * c };
}

vec2  vec2::getNormal() const
{
    vec2 normalized = this->normalize();
    return { -normalized.y, normalized.x };
}


// External function

vec2    Maths::getVec2(const vec2& pt1, const vec2& pt2)
{
    return pt2 - pt1;
}

float   Maths::getDistance(const vec2& pt1, const vec2& pt2)
{
    return getVec2(pt1, pt2).length();
}

//specific vector operation
float   Maths::angle2Degrees(const vec2& v1, const vec2& v2)
{
    return angle2(v1, v2) * RADTODEG;
}

vec2    Maths::rotate2(const vec2& pt, const vec2& center, float angle)
{
    vec2 v = getVec2(center, pt).getRotated(angle);

    return { center.x + v.x, center.y + v.y };
}

std::ostream& Maths::operator<<(std::ostream& o, vec2 f)
{
    return o << "x : " << f.x << ", y : " << f.y;
}

