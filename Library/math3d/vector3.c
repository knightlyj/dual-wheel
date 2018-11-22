#include "vector3.h"
#include "arm_math.h"

float Vector3_Dot(CL_Vector3_t* v1, CL_Vector3_t* v2)
{
    float res;
    arm_dot_prod_f32((float*)v1, (float*)v2, 3, &res);
    return res;
}

