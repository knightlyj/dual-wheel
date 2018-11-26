#pragma once

#include "mathex.h"
#include "vector3.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x, y, z, w;

    float mat[3][3]; //��ת����
} Quaternion;

//ȡ��
float Quaternion_Magnitude(const Quaternion* q);

//��׼��
void Quaternion_Normalize(Quaternion* q);

//ת��Ϊ��ͻ���
void Quaternion_ToRadianAxis(Quaternion* q, Vector3* axis, float* theta);

//����-���Ȼ�ȡ��Ԫ��
void Quaternion_FromRadianAxis(Quaternion* q, Vector3* axis, float theta, uint8_t normalized);

//��תv,out������v
void Quaternion_Rotate(const Quaternion* q, const Vector3* v, Vector3* out);

//���,out����ΪNULL,����Ϊq1��q2������ֵ
void Quaternion_Multiply(const Quaternion* q1, const Quaternion* q2, Quaternion* out);

//�ж����
uint8_t Quaternion_Equal(const Quaternion* q1, const Quaternion* q2);

void Quaternion_ToString(const Quaternion* q, char* buff);

#ifdef __cplusplus
}
#endif

