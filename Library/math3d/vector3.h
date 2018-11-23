#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct
    {
        float x, y, z;
    } Vector3;

    //点乘
    float Vector3_Dot(Vector3* v1, Vector3* v2);

    //叉乘,如果out为NULL,则结果放到v1
    void Vector3_Cross(Vector3* v1, Vector3* v2, Vector3* out);

    //取模
    float Vector3_Magnitude(Vector3* v);

    //模的平方
    float Vector3_SqrMagnitude(Vector3* v);

    //标准化
    void Vector3_Normalize(Vector3* v);

    //标量乘
    void Vector3_Scale(Vector3* v, float s, Vector3* out);

    //分量相乘,如果out为NULL,则结果放到v1
    void Vector3_Multiply(Vector3* v1, Vector3* v2, Vector3* out);

    //分量相加,如果out为NULL,则结果放到v1
    void Vector3_Add(Vector3* v1, Vector3* v2, Vector3* out);

    //分量相减,如果out为NULL,则结果放到v1
    void Vector3_Subtract(Vector3* v1, Vector3* v2, Vector3* out);

    //计算向量夹角
    float Vector3_Radian(Vector3* v1, Vector3* v2);

    //从v1到v2投影,如果out为NULL,则结果放到v1
    void Vector3_Project(Vector3* v1, Vector3* v2, Vector3* out);

    //从v1到normal所在平面投影,如果out为NULL,则结果放到v1
    void Vector3_ProjectOnPlane(Vector3* v1, Vector3* normal, Vector3* out);

    

    //打印
    void Vector3_ToString(char* buff, Vector3* v);

#ifdef __cplusplus
}
#endif
