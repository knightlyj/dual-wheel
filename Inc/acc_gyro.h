#pragma once

#include "cl_common.h"

typedef struct
{
    float acc_x;
    float acc_y;
    float acc_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;
} AccGyro_Data_t;

CL_RESULT AccGyro_Init(void);
CL_RESULT AccGro_GetData(AccGyro_Data_t* data);


