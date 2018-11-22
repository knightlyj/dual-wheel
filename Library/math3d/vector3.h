#pragma once

typedef struct
{
    float x,y,z;
} Vector3_t;

//点乘
float Vector3_Dot(Vector3_t* v1, Vector3_t* v2); 

//叉乘,如果out为NULL,则结果放到v1
void Vector3_Cross(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//取模
float Vector3_Magnitude(Vector3_t* v);

//模的平方
float Vector3_SqrMagnitude(Vector3_t* v);

//标准化
void Vector3_Normalize(Vector3_t* v);

//标量乘
void Vector3_Scale(Vector3_t* v, float s);

//从v1到v2投影,如果out为NULL,则结果放到v1
void Vector3_Project(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//从v1到normal所在平面投影,如果out为NULL,则结果放到v1
void Vector3_ProjectOnPlane(Vector3_t* v1, Vector3_t* normal, Vector3_t* out);

//分量相乘,如果out为NULL,则结果放到v1
void Vector3_Multiply(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//分量相加,如果out为NULL,则结果放到v1
void Vector3_Add(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);

//分量相减,如果out为NULL,则结果放到v1
void Vector3_Subtract(Vector3_t* v1, Vector3_t* v2, Vector3_t* out);



