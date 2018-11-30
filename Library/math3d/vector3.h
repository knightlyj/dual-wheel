#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct
    {
        float x, y, z;
    } Vector3;

    //���
    float Vector3_Dot(const Vector3* v1, const Vector3* v2);

    //���,out����Ϊv1��v2
    Vector3* Vector3_Cross(const Vector3* v1, const Vector3* v2, Vector3* out);

    //ȡģ
    float Vector3_Magnitude(const Vector3* v);

    //ģ��ƽ��
    float Vector3_SqrMagnitude(const Vector3* v);

    //��׼��
    void Vector3_Normalize(Vector3* v);

    //������,out����Ϊv
    Vector3* Vector3_Scale(const Vector3* v, float s, Vector3* out);

    //�������,out����Ϊv1��v2
    Vector3* Vector3_Multiply(const Vector3* v1, const Vector3* v2, Vector3* out);

    //�������,out����Ϊv1��v2
    Vector3* Vector3_Add(const Vector3* v1, const Vector3* v2, Vector3* out);

    //�������,out����Ϊv1��v2
    Vector3* Vector3_Subtract(const Vector3* v1, const Vector3* v2, Vector3* out);

    //���������н�
    float Vector3_Radian(const Vector3* v1, const Vector3* v2);

    //ͬ��,������cosֵ
    float Vector3_Cos(const Vector3* v1, const Vector3* v2);

    //��v1��v2ͶӰ,out����Ϊv1��v2
    Vector3* Vector3_Project(const Vector3* v1, const Vector3* v2, Vector3* out);

    //��v1��normal����ƽ��ͶӰ,out����Ϊv1��normal
    Vector3* Vector3_ProjectOnPlane(const Vector3* v1, const Vector3* normal, Vector3* out);

    //�ж����
    uint8_t Vector3_Equal(const Vector3* v1, const Vector3* v2);

    //��ӡ
    char* Vector3_ToString(const Vector3* v, char* buff);
   

#ifdef __cplusplus
}
#endif
