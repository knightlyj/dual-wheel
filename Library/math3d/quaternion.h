#pragma once

#include "vector3.h"
#include "math.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ANGLE_TO_RADIAN(angle)          ((float)angle * M_PI / 180.0f)
#define RADIAN_TO_ANGLE(radian)         (radian * 180 / M_PI)   

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

void Quaternion_ToString(const Quaternion* q, char* buff);

#ifdef __cplusplus
}
#endif

