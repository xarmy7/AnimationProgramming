#pragma once

#include <iostream>

namespace Maths
{
    class vec2
    {
    private:

    public:
        float           x = 0.f;
        float           y = 0.f;
        static vec2     i;
        static vec2     j;


        vec2();
        vec2(float _x, float _y);
        vec2(const vec2& f);
        ~vec2() = default;

        operator float*();

        vec2& operator=(const vec2& f);
        bool operator==(const vec2& f);

        vec2    operator-() const;
        void    operator-();
        void    operator+=(const vec2& f);
        vec2    operator+(const vec2& f);
        void    operator-=(const vec2& f);
        vec2    operator-(const vec2& f);

        void    operator*=(const vec2& f);
        vec2    operator*(const float f);
        vec2    operator*(const vec2 f);
        vec2    operator/(const float f);

        float   operator[](const int index) const;

        float   length() const;
        float   squareLength() const;
        vec2    normalize() const;
        vec2    getRotated(float angleDeg) const;
        vec2    getNormal() const;
    };

    // Operator
    vec2    operator-(const vec2& f1, const vec2& f2);

    //vector definition
    vec2    getVec2(const vec2& pt1, const vec2& pt2);
    float   getDistance(const vec2& pt1, const vec2& pt2);

    std::ostream& operator<<(std::ostream&, vec2 f);
    float   dot2(const vec2& v1, const vec2& v2);
    float   angle2(const vec2& v1, const vec2& v2);

    float   angle2Degrees(const vec2& v1, const vec2& v2);
    vec2    rotate2(const vec2& pt, const vec2& center, float angle);

}
