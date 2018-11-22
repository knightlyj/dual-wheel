#pragma once

typedef struct
{
    float x,y,z;
} Vector3_t;

//���
float Vector3_Dot(Vector3_t* v1, Vector3_t* v2); 

//���,���outΪNULL,�����ŵ�v1
void Vector3_Cross(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//ȡģ
float Vector3_Magnitude(Vector3_t* v);

//ģ��ƽ��
float Vector3_SqrMagnitude(Vector3_t* v);

//��׼��
void Vector3_Normalize(Vector3_t* v);

//������
void Vector3_Scale(Vector3_t* v, float s);

//��v1��v2ͶӰ,���outΪNULL,�����ŵ�v1
void Vector3_Project(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//��v1��normal����ƽ��ͶӰ,���outΪNULL,�����ŵ�v1
void Vector3_ProjectOnPlane(Vector3_t* v1, Vector3_t* normal, Vector3_t* out);

//�������,���outΪNULL,�����ŵ�v1
void Vector3_Multiply(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//�������,���outΪNULL,�����ŵ�v1
void Vector3_Add(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//�������,���outΪNULL,�����ŵ�v1
void Vector3_Subtract(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);



