#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct
    {
        float x, y, z;
    } Vector3;

    //���
    float Vector3_Dot(Vector3* v1, Vector3* v2);

    //���,���outΪNULL,�����ŵ�v1
    void Vector3_Cross(Vector3* v1, Vector3* v2, Vector3* out);

    //ȡģ
    float Vector3_Magnitude(Vector3* v);

    //ģ��ƽ��
    float Vector3_SqrMagnitude(Vector3* v);

    //��׼��
    void Vector3_Normalize(Vector3* v);

    //������
    void Vector3_Scale(Vector3* v, float s, Vector3* out);

    //�������,���outΪNULL,�����ŵ�v1
    void Vector3_Multiply(Vector3* v1, Vector3* v2, Vector3* out);

    //�������,���outΪNULL,�����ŵ�v1
    void Vector3_Add(Vector3* v1, Vector3* v2, Vector3* out);

    //�������,���outΪNULL,�����ŵ�v1
    void Vector3_Subtract(Vector3* v1, Vector3* v2, Vector3* out);

    //���������н�
    float Vector3_Radian(Vector3* v1, Vector3* v2);

    //��v1��v2ͶӰ,���outΪNULL,�����ŵ�v1
    void Vector3_Project(Vector3* v1, Vector3* v2, Vector3* out);

    //��v1��normal����ƽ��ͶӰ,���outΪNULL,�����ŵ�v1
    void Vector3_ProjectOnPlane(Vector3* v1, Vector3* normal, Vector3* out);

    

    //��ӡ
    void Vector3_ToString(char* buff, Vector3* v);

#ifdef __cplusplus
}
#endif
