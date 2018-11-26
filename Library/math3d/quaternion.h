#pragma once

#include "vector3.h"
#include "math.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ANGLE_TO_RADIAN(angle)          ((float)angle * M_PI / 180.0f)
#define RADIAN_TO_ANGLE(radian)         (randian * 180 / M_PI)   

typedef struct
{
    float x, y, z, w;

    float mat[3][3]; //旋转矩阵
} Quaternion;

//取摸
float Quaternion_Magnitude(Quaternion* q);

//标准化
void Quaternion_Normalize(Quaternion* q);

//转换为轴和弧度
void Quaternion_ToRadianAxis(Quaternion* q, Vector3* axis, float* theta, uint8_t normalized);

//从轴-弧度获取四元数
void Quaternion_FromRadianAxis(Quaternion* q, Vector3* axis, float theta, uint8_t normalized);

//旋转v,如果out为NULL,则把结果放在v
void Quaternion_Rotate(Quaternion* q, Vector3* v, Vector3* out);

//相乘,out不能为NULL,可以为q1或q2或其他值
void Quaternion_Multiply(Quaternion* q1, Quaternion* q2, Quaternion* out);

#ifdef __cplusplus
}
#endif

