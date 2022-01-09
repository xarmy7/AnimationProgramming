
#include <iostream>
#include <string>

#include "Maths/maths.hpp"

using namespace Maths;

vec3 Maths::operator*(const Maths::mat4& m, Maths::vec3 v)
{
    return M4x4::multiplyPoint(m, v);
}

vec4 Maths::operator*(const mat4& m, vec4 v)
{
    vec4 res = { 0.f, 0.f, 0.f, 0.f };

    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            res[line] += *(&m.l[column].x + line) * v[column];
        }
    }

    return res;
}

mat4 Maths::operator*(const mat4& a, const mat4& b)
{
    mat4 res = M4x4::null();

    for (int line = 0; line < 4; ++line)
    {
        for (int column = 0; column < 4; ++column)
        {
            for (int vect = 0; vect < 4; ++vect)
                res.l[column][line] += *(&a.l[vect].x + line) * b.l[column].index(vect);
        }
    }

    return res;
}


// MVP OPERATION
// -------------

vec3 M4x4::multiplyPoint(const mat4& m, const vec3& point)
{
    const float w = m.e[3] * point.x + m.e[7] * point.y + m.e[11] * point.z + m.e[15];
    
    return {
        (m.e[0] * point.x + m.e[4] * point.y + m.e[8] * point.z + m.e[12]) / w,
        (m.e[1] * point.x + m.e[5] * point.y + m.e[9] * point.z + m.e[13]) / w,
        (m.e[2] * point.x + m.e[6] * point.y + m.e[10] * point.z + m.e[14]) / w
    };
}


mat4 M4x4::frustum(float left, float right, float bottom, float top, float near, float far)
{
    return
    {
        (near * 2.f) / (right - left),   0.f,                              0.f,                               0.f,
        0.f,                             (near * 2.f) / (top - bottom),    0.f,                               0.f,
        (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near),      -1.f,
        0.f,                             0.f,                             -(far * near * 2.f) / (far - near), 0.f
    };
}

mat4 M4x4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    float rightLeft = right - left;
    float topBottom = top - bottom;
    float farNear = far - near;

    return
    {
        2.f / rightLeft,                0.f,                         0.f,                       0.f,
        0.f,                            2.f / topBottom,             0.f,                       0.f,
        0.f,                            0.f,                        -2 / farNear,               0.f,
       -(right + left) / rightLeft,    -(top + bottom) / topBottom, -(near + far) / farNear,    1.f
    };
}

mat4 M4x4::perspective(float fovY, float aspect, float near, float far, bool ortho)
{
    float top;
    if (ortho) top = tanf(Maths::DEGTORAD * fovY * 0.5f);
    else top = near * tanf(Maths::DEGTORAD * fovY * 0.5f);
    float right = top * aspect;
    float bottom = -top, left = -right;
    return ortho ? orthographic(left, right, bottom, top, near, far) : frustum(left, right, bottom, top, near, far);
}




// TRS OPERATION
// -------------


vec3 M4x4::position(const mat4& matrix)
{
    return vec3(matrix.l[3].index(0), matrix.l[3].index(1), matrix.l[3].index(2));
}

mat4 M4x4::rotateX(float angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, cos, sin, 0.f,
        0.f,-sin, cos, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

mat4 M4x4::rotateY(float angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        cos, 0.f, -sin, 0.f,
        0.f, 1.f,  0.f, 0.f,
        sin, 0.f,  cos, 0.f,
        0.f, 0.f,  0.f, 1.f
    };
}

mat4 M4x4::rotateZ(float angleRadians)
{

    float cos = cosf(angleRadians), sin = sinf(angleRadians);
    return {
         cos, sin, 0.f, 0.f,
        -sin, cos, 0.f, 0.f,
         0.f, 0.f, 1.f, 0.f,
         0.f, 0.f, 0.f, 1.f
    };
}

mat4 M4x4::rotateXYZ(const vec3& r)
{
    return  rotateY(r.y) * rotateX(r.x) * rotateZ(r.z);
}

mat4 M4x4::translate(float x, float y, float z, float w)
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        x,   y,   z,   w
    };
}

mat4 M4x4::translate(vec3 f)
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        f.x, f.y, f.z, 1.f
    };
}

mat4 M4x4::scale(float sc)
{
    return {
        sc, 0.f, 0.f, 0.f,
        0.f, sc, 0.f, 0.f,
        0.f, 0.f, sc, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

mat4 M4x4::scale(vec3 sc)
{
    return {
    sc.x,   0.f,    0.f,    0.f,
    0.f,    sc.y,   0.f,    0.f,
    0.f,    0.f,    sc.z,   0.f,
    0.f,    0.f,    0.f,    1.f
    };
}

mat4 M4x4::inverse(const mat4& mat)
{
    mat4 result = { 0 };

    float a00 = mat.e[0], a01 = mat.e[1], a02 = mat.e[2], a03 = mat.e[3];
    float a10 = mat.e[4], a11 = mat.e[5], a12 = mat.e[6], a13 = mat.e[7];
    float a20 = mat.e[8], a21 = mat.e[9], a22 = mat.e[10], a23 = mat.e[11];
    float a30 = mat.e[12], a31 = mat.e[13], a32 = mat.e[14], a33 = mat.e[15];

    float b00 = a00 * a11 - a01 * a10;
    float b01 = a00 * a12 - a02 * a10;
    float b02 = a00 * a13 - a03 * a10;
    float b03 = a01 * a12 - a02 * a11;
    float b04 = a01 * a13 - a03 * a11;
    float b05 = a02 * a13 - a03 * a12;
    float b06 = a20 * a31 - a21 * a30;
    float b07 = a20 * a32 - a22 * a30;
    float b08 = a20 * a33 - a23 * a30;
    float b09 = a21 * a32 - a22 * a31;
    float b10 = a21 * a33 - a23 * a31;
    float b11 = a22 * a33 - a23 * a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

    result.e[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
    result.e[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
    result.e[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
    result.e[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
    result.e[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
    result.e[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
    result.e[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
    result.e[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
    result.e[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
    result.e[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
    result.e[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
    result.e[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
    result.e[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
    result.e[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
    result.e[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
    result.e[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

    return result;
}

std::string M4x4::getStrMatrice(mat4 m)
{
    std::string  s;
    for (int i = 0; i < 16; ++i)
    {
        s += std::to_string(m.e[i]) + ", ";
        s += (i + 1) % 4 == 0 ? "\n" : "";
    }
    return s;
}

std::ostream& operator<<(std::ostream& o, mat4 m)
{
    return o << M4x4::getStrMatrice(m);
}