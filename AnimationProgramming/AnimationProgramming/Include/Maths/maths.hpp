#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "quaternion.hpp"

namespace Maths
{
    const float TAU = 6.283185307179586476925f;
    const float PI = 3.14159265358979323846f;
    const float PI_HALF = PI / 2.f;
    const float DEGTORAD = (PI / 180.f);
    const float RADTODEG = (180.f / PI);
    const float EPSILON = (float)pow(2, -24);

    template<typename T>
    inline T min(T a, T b) { return a < b ? a : b; }
    template<typename T>
    inline T max(T a, T b) { return a > b ? a : b; }
    template<typename T>
    inline T min(T a, T b, T c) { return min(min(a, b), c); }
    template<typename T>
    inline T max(T a, T b, T c) { return max(max(a, b), c); }

    template<typename T>
    inline T clamp(T val, T _min, T _max) 
    {
        return max(min(val, _max), _min); 
    }
    inline vec3 clamp(vec3 v, float min, float max)
    {
        return vec3(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
    }
    inline vec4 clamp(vec4 v, float min, float max)
    {
        return vec4(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max));
    }

    inline float square(float f) { return f * f; }
    inline float cos(float f) { return cosf(f); }
    inline float sin(float f) { return sinf(f); }
    inline float tan(float f) { return tanf(f); }

    template<typename T>
    inline T lerp(T start, T reach, float factor) { return start + factor * (reach - start); }

    inline Quaternion slerp(Quaternion& q1, Quaternion& q2, float factor)
    {
        Quaternion result;

        float cosHalfTheta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

        if (cosHalfTheta < 0.f)
        {
            q2 = -q2;
            cosHalfTheta = -cosHalfTheta;
        }

        if (fabs(cosHalfTheta) >= 1.0f) result = q1;
        ///else if (cosHalfTheta > 0.95f) result = QuaternionNlerp(q1, q2, factor);
        else
        {
            float halfTheta = acosf(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (fabs(sinHalfTheta) < 0.001f)
            {
                result.x = (q1.x * 0.5f + q2.x * 0.5f);
                result.y = (q1.y * 0.5f + q2.y * 0.5f);
                result.z = (q1.z * 0.5f + q2.z * 0.5f);
                result.w = (q1.w * 0.5f + q2.w * 0.5f);
            }
            else
            {
                float ratioA = sinf((1 - factor) * halfTheta) / sinHalfTheta;
                float ratioB = sinf(factor * halfTheta) / sinHalfTheta;

                result.x = (q1.x * ratioA + q2.x * ratioB);
                result.y = (q1.y * ratioA + q2.y * ratioB);
                result.z = (q1.z * ratioA + q2.z * ratioB);
                result.w = (q1.w * ratioA + q2.w * ratioB);
            }
        }

        return result;
    }

    // return 1 if positive and -1 if not
    template <typename T> 
    inline int sign(T val) { return (T(0) < val) - (val < T(0)); }

    inline bool isNumber(char charNumber)
    {
        return (charNumber >= 45 && charNumber < 58 && // '-', '.', '0', '1'...'9'
            charNumber != 47); // '/'
    }
    inline bool isInt(char charNumber)
    {
        return (charNumber >= 48 && charNumber < 58); // '0', '1'...'9'
    }

    /////////////////////////// RANGE

    struct range
    {
        float min = 0.f, max = 0.f;
    };

    // Range operation
    inline range    rangeMerge(const range& range1, const range& range2)
    {
        return { min(range1.min, range2.min), max(range1.max, range2.max) };
    }

    inline range    rangeSort(const range& r)
    {
        return rangeMerge(r, { r.max, r.min });
    }

    inline range    rangeMergeByValue(const range& range1, float value)
    {
        return { min(range1.min, value), max(range1.max, value) };
    }

    inline bool     isRangeCollision(const range& range1, const range& range2)
    {
        return !((range1.min > range2.max) || (range2.min > range1.max));
    }

    inline range    pointProjection(const vec3& pt, const vec3& axis)
    {
        float projection = dot(pt, axis);
        return { projection, projection };
    }
}

