#pragma once

#include "cl_common.h"
#include "vector3.h"

CL_RESULT BMI160_Init(void);
CL_RESULT BMI160_GetData(Vector3* accData, Vector3* gyroData);



