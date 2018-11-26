#pragma once

#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INFINIT_SMALL   (0.000001f)

//�жϸ��������
#define FLOAT_EQUAL(f1, f2)     (fabs(f1 - f2) < INFINIT_SMALL)

//�Ƕ�תΪ����
#define ANGLE_TO_RADIAN(angle)          ((float)angle * M_PI / 180.0f)

//����תΪ�Ƕ�
#define RADIAN_TO_ANGLE(radian)         (radian * 180 / M_PI)   


#ifdef __cplusplus
}
#endif
