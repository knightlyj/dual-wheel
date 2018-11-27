#include "attitude.h"
#include "sensors.h"
#include "mathex.h"
#include "cl_fsm.h"
#include "sys_time.h"

void CalibrateStart(CL_Fsm_t* CL_Fsm)
{

}

void CalibrateUpdate(CL_Fsm_t* CL_Fsm, uint16_t interval)
{
    AccelData_t accData;
    float totalAccel;

    if(BMI160_GetData(&accData, CL_NULL) == CL_SUCCESS)
    {
        totalAccel = sqrt(accData.x * accData.x
                          + accData.y * accData.y
                          + accData.z * accData.z);
        Log("total accel: %.3f\r\n", totalAccel);
//        Log("acc: %.2f, %.2f, %.2f\r\n", sensorData.acc_x, sensorData.acc_y, sensorData.acc_z);
//        Log("gyro: %.2f, %.2f, %.2f\r\n", sensorData.gyro_x, sensorData.gyro_y, sensorData.gyro_z);
    }
    else
    {
        Log("read sensor failed\r\n");
    }
}


void AttCalcStart(CL_Fsm_t* CL_Fsm)
{

}

void AttCalcUpdate(CL_Fsm_t* CL_Fsm, uint16_t interval)
{

}

static CL_FsmState_t fsmStates[] =
{
    CL_FSM_STATE(CalibrateStart, CalibrateUpdate, CL_NULL),  //Ð£×¼
    CL_FSM_STATE(AttCalcStart, AttCalcUpdate, CL_NULL),  //×ËÌ¬½âËã 
};

CL_FSM_DEF_INIT(AttitudeFsm, fsmStates);


void Attitude_Process(void)
{
    static uint64_t lastTime = 0;
    uint16_t interval;    
    interval = TimeElapsed(lastTime);
    SetToCurTime(&lastTime);

    
    CL_FsmUpdate(&AttitudeFsm, interval);
}









