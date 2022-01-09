#pragma once

#include "vec4.hpp"

// Matrice translation (line config) :
// 1 0 0 0
// 0 1 0 0
// 0 0 1 0
// 1 1 1 1


namespace Maths
{
    union mat4
    {
        float e[16];
        vec4 l[4];
    };

    namespace M4x4
    {
        inline mat4 identity()
        {
            return {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f,
            };
        }

        inline mat4 null()
        {
            return {
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
            };
        }

        vec3 multiplyPoint(const mat4& m, const vec3& point);

        mat4 frustum(float left, float right, float bottom, float top, float near, float far);
        mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
        mat4 perspective(float fovY, float aspect, float near, float far, bool ortho = false);

        vec3 position(const mat4& matrix);

        mat4 rotateX(float angleRadians);
        mat4 rotateY(float angleRadians);
        mat4 rotateZ(float angleRadians);
        mat4 rotateXYZ(const vec3& anglesRadians);

        mat4 translate(float x, float y, float z, float w = 1.f);
        mat4 translate(vec3 f);

        mat4 scale(float sc);
        mat4 scale(vec3 sc);

        mat4 inverse(const mat4& m);

        std::string getStrMatrice(mat4 m);
    }
    // OPERATION
    Maths::vec3 operator*(const Maths::mat4& m, Maths::vec3 v);
    Maths::vec4 operator*(const Maths::mat4& m, Maths::vec4 v);
    Maths::mat4 operator*(const Maths::mat4& a, const Maths::mat4& b);
};


std::ostream& operator<<(std::ostream& o, Maths::mat4 m);
