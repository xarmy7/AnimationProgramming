
#include "Maths/maths.hpp"

using namespace Maths;

mat4 Maths::quaternionToMatrix(const Quaternion& q)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xz = q.x * q.z, xy = q.x * q.y, xw = q.x * q.w;
    float yz = q.y * q.z, yw = q.y * q.w, zw = q.z * q.w;

    return {
        1 - 2*(yy + zz),    2*(xy + zw),        2*(xz - yw),        0.f,
        2*(xy - zw),        1 - 2*(xx + zz),    2*(yz + xw),        0.f,
        2*(xz + yw),        2*(yz - xw),        1 - 2*(xx + yy),    0.f,
        0.f,                0.f,                0.f,                1.f
    };

    /*
    m[0][0] = 1 - 2 * (quat[1] * quat[1] + quat[2] * quat[2]);
    m[0][1] = 2 * (quat[0] * quat[1] + quat[3] * quat[2]);
    m[0][2] = 2 * (quat[0] * quat[2] - quat[3] * quat[1]);

    // Second row of the rotation matrix
    m[1][0] = 2 * (quat[0] * quat[1] - quat[3] * quat[2]);
    m[1][1] = 1 - 2 * (quat[0] * quat[0] + quat[2] * quat[2]);
    m[1][2] = 2 * (quat[1] * quat[2] + quat[3] * quat[0]);

    // Third row of the rotation matrix
    m[2][0] = 2 * (quat[0] * quat[2] + quat[3] * quat[1]);
    m[2][1] = 2 * (quat[1] * quat[2] - quat[3] * quat[0]);
    m[2][2] = 1 - 2 * (quat[0] * quat[0] + quat[1] * quat[1]);
    */
}

Quaternion Maths::quaternionConjugate(const Quaternion& q)
{
    // Q = x + y + z + w , Q.conjugate = -x - y - z + w 
    return { -q.x, -q.y, -q.z, q.w };
}

Quaternion Maths::quaternionInverse(const Quaternion& q)
{
    return quaternionConjugate(q) * (1 / q.squareLength());
}

Quaternion Maths::quaternionFromVectors(const vec3& from, const vec3& to)
{
    vec3 crossed = cross(from, to);
    return Quaternion(crossed.x, crossed.y, crossed.z, 1.0f + dot(from, to)).normalize();
}

Quaternion Maths::quaternionFromAxisAngle(const vec3& axis, float angle)
{
    Quaternion result = quaternionIdentity();

    if (axis.length() != 0.0)
        angle *= 0.5;

    vec3 n = axis.normalize();

    auto sinres = sinf(angle);
    auto cosres = cosf(angle);

    result.x = n.x * sinres;
    result.y = n.y * sinres;
    result.z = n.z * sinres;
    result.w = cosres;
    return result.normalize();
}

void Maths::quaternionToAxisAngle(const Quaternion& q, vec3& axis, float& angle)
{
    Quaternion normalized = q;
    if (fabs(q.w) > 1.0f) normalized = quaternionNormalize(q);

    vec3 resAxis = vec3();
    float resAngle = 2.0f * acosf(normalized.w);
    float den = sqrtf(1.0f - normalized.w * normalized.w);

    if (den > 0.0001f)
    {
        resAxis.x = normalized.x / den;
        resAxis.y = normalized.y / den;
        resAxis.z = normalized.z / den;
    }
    else
        resAxis.x = 1.0f;

    axis = resAxis;
    angle = resAngle;
}

Quaternion Maths:: quaternionFromEulerAngles(float roll, float pitch, float yaw)
{
    float x0 = Maths::cos(roll * 0.5f);
    float x1 = Maths::sin(roll * 0.5f);
    float y0 = Maths::cos(pitch * 0.5f);
    float y1 = Maths::sin(pitch * 0.5f);
    float z0 = Maths::cos(yaw * 0.5f);
    float z1 = Maths::sin(yaw * 0.5f);

    return Quaternion(
        (x1 * y0 * z0) - (x0 * y1 * z1),
        (x0 * y1 * z0) + (x1 * y0 * z1),
        (x0 * y0 * z1) - (x1 * y1 * z0),
        (x0 * y0 * z0) + (x1 * y1 * z1)
    );
}

Quaternion Maths::quaternionFromEulerAngles(const vec3& radAngles)
{
    return quaternionFromEulerAngles(radAngles.x, radAngles.y, radAngles.z);
}

vec3 Maths::quaternionToEulerAngles(const Quaternion& q)
{
    // roll (x-axis rotation)
    float x0 = 2.0f * (q.w * q.x + q.y * q.z);
    float x1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

    // pitch (y-axis rotation)
    float y0 = 2.0f * (q.w * q.y - q.z * q.x);
    y0 = clamp(y0, -1.0f, 1.0f);

    // yaw (z-axis rotation)
    float z0 = 2.0f * (q.w * q.z + q.x * q.y);
    float z1 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);

    return vec3(atan2f(x0, x1), asinf(y0), atan2f(z0, z1));
}

vec3 Maths::vectorRotateByQuaternion(const vec3& v, const Quaternion& q)
{
    float qx_square = q.x * q.x, qy_square = q.y * q.y, qz_square = q.z * q.z, qw_square = q.w * q.w;
    // From operation " v' = q(rot) * q(vector) * q(rot).conjugate "
    return	{
        // X coord
        v.x * (qx_square - qy_square - qz_square + qw_square) +
        v.y * (2.0f * q.x * q.y - 2.0f * q.w * q.z) +
        v.z * (2.0f * q.x * q.z + 2.0f * q.w * q.y),
        // Y coord
        v.x * (2.0f * q.w * q.z + 2.0f * q.x * q.y) +
        v.y * (-qx_square + qy_square - qz_square + qw_square) +
        v.z * (-2.0f * q.w * q.x + 2.0f * q.y * q.z),
        // Z coord
        v.x * (-2.0f * q.w * q.y + 2.0f * q.x * q.z) +
        v.y * (2.0f * q.w * q.x + 2.0f * q.y * q.z) +
        v.z * (-qx_square - qy_square + qz_square + qw_square)
    };
}


vec3	Maths::getNormalFromQuaternion(const Quaternion& q)
{
    return vectorRotateByQuaternion({ 0.f, 1.f, 0.f }, q);
}
Quaternion	Maths::getQuaternionFromNormal(const vec3& normal)
{
    vec3 n = normal;
    return quaternionFromVectors({ 0.f, 1.f, 0.f }, n);
}