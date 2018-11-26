#include "quaternion.h"

static void UpdateMatrix(Quaternion* q)
{
    q->mat[0][0] = 1 - 2 * (q->y * q->y + q->z * q->z);
    q->mat[0][1] = 2 * (q->x * q->y - q->w * q->z);
    q->mat[0][2] = 2 * (q->x * q->z + q->w * q->y);

    q->mat[1][0] = 2 * (q->x * q->y + q->w * q->z);
    q->mat[1][1] = 1 - 2 * (q->x * q->x + q->z * q->z);
    q->mat[1][2] = 2 * (q->y * q->z - q->w * q->x);

    q->mat[2][0] = 2 * (q->x * q->z - q->w * q->y);
    q->mat[2][1] = 2 * (q->y * q->z + q->w * q->x);
    q->mat[2][2] = 1 - 2 * (q->x * q->x + q->y * q->y);
}


float Quaternion_Magnitude(Quaternion* q)
{
    return sqrtf(q->x * q->x
                 + q->y * q->y
                 + q->z * q->z
                 + q->w * q->w);
}


void Quaternion_Normalize(Quaternion* q)
{
    float s = 1.0f / Quaternion_Magnitude(q);

    q->x *= s;
    q->y *= s;
    q->z *= s;
    q->w *= s;

    UpdateMatrix(q);
}

void Quaternion_ToRadianAxis(Quaternion* q, Vector3* axis, float* theta, uint8_t normalized)
{
    if (!normalized)
        Quaternion_Normalize(q);

    *theta = acosf(q->w) * 2;

    axis->x = q->x;
    axis->y = q->y;
    axis->z = q->z;

    Vector3_Normalize(axis);
}

void Quaternion_FromRadianAxis(Quaternion* q, Vector3* axis, float theta, uint8_t normalized)
{
    float cosHalfTheta, sinHalfTheta, halfTheta;
    if (!normalized)
        Vector3_Normalize(axis);

    halfTheta = theta / 2.0f;
    cosHalfTheta = cosf(halfTheta);
    sinHalfTheta = sinf(halfTheta);

    q->w = cosHalfTheta;
    q->x = sinHalfTheta * axis->x;
    q->y = sinHalfTheta * axis->y;
    q->z = sinHalfTheta * axis->z;

    UpdateMatrix(q);
}


void Quaternion_Rotate(Quaternion* q, Vector3* v, Vector3* out)
{
    float x, y, z;
    x = q->mat[0][0] * v->x + q->mat[0][1] * v->y + q->mat[0][2] * v->z;
    y = q->mat[1][0] * v->x + q->mat[1][1] * v->y + q->mat[1][2] * v->z;
    z = q->mat[2][0] * v->x + q->mat[2][1] * v->y + q->mat[2][2] * v->z;
    if (out)
    {
        out->x = x;
        out->y = y;
        out->z = z;
    }
    else
    {
        v->x = x;
        v->y = y;
        v->z = z;
    }
}

void Quaternion_Multiply(Quaternion* q1, Quaternion* q2, Quaternion* out)
{
    Vector3 v;
    out->w = q1->w * q2->w - Vector3_Dot((Vector3*)q1, (Vector3*)q2);

    Vector3_Cross((Vector3*)q1, (Vector3*)q2, &v);

    v.x += q1->w * q2->x + q2->w * q1->x;
    v.y += q1->w * q2->y + q2->w * q1->y;
    v.z += q1->w * q2->z + q2->w * q1->z;

    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
}

