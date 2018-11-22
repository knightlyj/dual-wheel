#pragma once
#include "vector3.h"

typedef struct
{
    float x,y,z,w;
} Quaternion_t;

//��׼��
void Quaternion_Normalize(Quaternion_t* q);

//ת��Ϊ��ͽǶ�
void Quaternion_ToAngleAxis(Vector3_t* axis, float* angle);

//����-�ǶȻ�ȡ��Ԫ��
void Quaternion_FromAngleAxis(Quaternion_t* q, Vector3_t* axis, float angle);

//��תv,���outΪNULL,��ѽ������v
void Quaternion_Rotate(Quaternion_t* q, Vector3_t* v, Vector3_t* out);



