#pragma once
#include "vector3.h"

typedef struct
{
    float x,y,z,w;
} Quaternion_t;

//��׼��
void Quaternion_Normalize(Quaternion_t* q);

//ת��Ϊ��ͽǶ�
void Quaternion_ToAngleAxis(Vector3* axis, float* angle);

//����-�ǶȻ�ȡ��Ԫ��
void Quaternion_FromAngleAxis(Quaternion_t* q, Vector3* axis, float angle);

//��תv,���outΪNULL,��ѽ������v
void Quaternion_Rotate(Quaternion_t* q, Vector3* v, Vector3* out);



