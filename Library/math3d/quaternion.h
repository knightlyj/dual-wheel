#pragma once
#include "vector3.h"

typedef struct
{
    float x,y,z,w;
} Quaternion_t;

//标准化
void Quaternion_Normalize(Quaternion_t* q);

//转换为轴和角度
void Quaternion_ToAngleAxis(Vector3_t* axis, float* angle);

//从轴-角度获取四元数
void Quaternion_FromAngleAxis(Quaternion_t* q, Vector3_t* axis, float angle);

//旋转v,如果out为NULL,则把结果放在v
void Quaternion_Rotate(Quaternion_t* q, Vector3_t* v, Vector3_t* out);



