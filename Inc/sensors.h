#pragma once

#include "cl_common.h"

typedef struct
{
    float x,y,z;
} AccelData_t;

typedef struct
{
    float x,y,z;
} GyroData_t;

CL_RESULT BMI160_Init(void);
CL_RESULT BMI160_GetData(AccelData_t* accData, GyroData_t* gyroData);

CL_RESULT BMI160_CalibrateAccel(void);



