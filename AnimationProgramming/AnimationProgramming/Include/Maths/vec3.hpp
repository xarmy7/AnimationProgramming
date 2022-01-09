#pragma once

#include <iostream>

namespace Maths
{
    class vec2;
    class vec4;

    class vec3
    {
    private:

    public:
        float       x = 0.f, y = 0.f, z = 0.f;
        static vec3 zero;
        static vec3 right, left, up, down, forward, backward;

        vec3();
        vec3(float equal);
        vec3(float _x, float _y, float _z);
        vec3(const vec3& f);
        vec3(const vec2& v2);
        vec3(const vec4& v4);
        ~vec3() = default;

        operator float* ();

        vec3& operator=(const vec3& f);
        bool operator==(const vec3& f);

        vec3  operator-() const;
        void    operator+=(const vec3& f);
        vec3  operator+(const vec3& f);
        vec3  operator+(const float& f) const;
        void    operator-=(const vec3& f);
        vec3  operator-(const vec3& f);

        void    operator*=(const vec3& f);
        vec3  operator*(const float f);
        vec3  operator*(const vec3 f) const;
        vec3  operator/(const float f);

        vec3  operator^(const vec3 f);

        float   operator[](const int index) const;

        float   length() const;
        float   squareLength() const;
        vec3    normalize() const;
        vec3    negate() const;
        vec3    reflect(const vec3& normal);

        bool equals(const vec3& toComapre) const;
    };

    vec3    operator-(const vec3& f1, const vec3& f2);
    vec3    operator+(const vec3& f1, const vec3& f2);
    vec3    operator*(const vec3& f1, const float f2);
    vec3  operator*(float f, vec3 v);
    std::ostream& operator<<(std::ostream&, vec3 f);

    float   dot(vec3 v1, vec3 v2);
    vec3    cross(const vec3& v1, const vec3& v2);
    float   angle(vec3 v1, vec3 v2);
}

