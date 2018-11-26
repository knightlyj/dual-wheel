#include "vector3.h"
#include "stdio.h"
#include "mathex.h"

float Vector3_Dot(const Vector3* v1, const Vector3* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void Vector3_Cross(const Vector3* v1, const Vector3* v2, Vector3* out)
{
    float a, b, c;
    a = v1->y * v2->z - v1->z * v2->y;
    b = v1->z * v2->x - v1->x * v2->z;
    c = v1->x * v2->y - v1->y * v2->x;

    out->x = a;
    out->y = b;
    out->z = c;
}

float Vector3_Magnitude(const Vector3* v)
{
    return sqrtf(v->x * v->x
        + v->y * v->y
        + v->z * v->z);
}


float Vector3_SqrMagnitude(const Vector3* v)
{
    return (v->x * v->x
        + v->y * v->y
        + v->z * v->z);
}


void Vector3_Normalize(Vector3* v)
{
    float s;
    s = 1.0f / Vector3_Magnitude(v);
    v->x *= s;
    v->y *= s;
    v->z *= s;
}


void Vector3_Scale(const Vector3* v, float s, Vector3* out)
{
    out->x = v->x * s;
    out->y = v->y * s;
    out->z = v->z * s;
}

float Vector3_Radian(const Vector3* v1, const Vector3* v2)
{
    float cos;

    cos = Vector3_Dot(v1, v2) / Vector3_Magnitude(v1) / Vector3_Magnitude(v2);
    return acosf(cos);
}

void Vector3_Project(const Vector3* v1, const Vector3* v2, Vector3* out)
{
    float s = 1.0f / Vector3_SqrMagnitude(v2);
    float dot = Vector3_Dot(v1, v2);

    out->x = v2->x * s * dot;
    out->y = v2->y * s * dot;
    out->z = v2->z * s * dot;
}


void Vector3_ProjectOnPlane(const Vector3* v1, const Vector3* normal, Vector3* out)
{
    float s = 1.0f / Vector3_SqrMagnitude(normal);
    float dot = Vector3_Dot(v1, normal);

    out->x = v1->x - normal->x * s * dot;
    out->y = v1->y - normal->y * s * dot;
    out->z = v1->z - normal->z * s * dot;
}

void Vector3_Multiply(const Vector3* v1, const Vector3* v2, Vector3* out)
{
    out->x = v1->x * v2->x;
    out->y = v1->y * v2->y;
    out->z = v1->z * v2->z;
}


void Vector3_Add(const Vector3* v1, const Vector3* v2, Vector3* out)
{
    out->x = v1->x + v2->x;
    out->y = v1->y + v2->y;
    out->z = v1->z + v2->z;
}


void Vector3_Subtract(const Vector3* v1, const Vector3* v2, Vector3* out)
{
    out->x = v1->x - v2->x;
    out->y = v1->y - v2->y;
    out->z = v1->z - v2->z;
}

uint8_t Vector3_Equal(const Vector3* v1, const Vector3* v2)
{
    Vector3 diff;
    Vector3_Subtract(v1, v2, &diff);
    float sqrMag = Vector3_SqrMagnitude(&diff);

    return FLOAT_EQUAL(Vector3_SqrMagnitude(&diff), 0);
}

void Vector3_ToString(const Vector3* v, char* buff)
{
    sprintf(buff, "{%.2f, %.2f, %.2f}", v->x, v->y, v->z);
}


