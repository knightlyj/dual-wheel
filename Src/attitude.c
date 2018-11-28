#include "attitude.h"
#include "sensors.h"
#include "mathex.h"
#include "sys_time.h"
#include "cl_queue.h"


#define STABLE_SAMPLE_NUM    100
#define STABLE_THRESHOLD     (0.05f)
CL_QUEUE_DEF_INIT(acc_q, STABLE_SAMPLE_NUM, Vector3, static);

char buff[256];

static CL_BOOL IsAccelStable(Vector3* sample, Vector3* out)
{
    Vector3* v;
    Vector3 average = {0,0,0};
    Vector3 diff;

    if(CL_QueueFull(&acc_q))
    {
        CL_QueuePoll(&acc_q, &diff);
    }

    CL_QueueAdd(&acc_q, sample);

    if(CL_QueueFull(&acc_q))
    {
        //�Ѳ���100��

        //�����ƽ��ֵ
        CL_QUEUE_FOR_EACH(&acc_q, v, Vector3)
        {
            Vector3_Add(&average, v, &average);
        }
        Vector3_Scale(&average, (1.0f / STABLE_SAMPLE_NUM), &average);

        //�ж�ÿ�β�����ƽ��ֵ�Ĳ�ֵ
        CL_QUEUE_FOR_EACH(&acc_q, v, Vector3)
        {
            Vector3_Subtract(&average, v, &diff);
            
            if(Vector3_SqrMagnitude(&diff) >= STABLE_THRESHOLD)
            {
                //�������һ����ֵ����,��û�ȶ�
                return CL_FALSE;
            }
        }

        //���в������ǳ��ӽ�,���Ѿ��ȶ�
        out->x = average.x;
        out->y = average.y;
        out->z = average.z;
        return CL_TRUE;
    }

    return CL_FALSE;
}



Vector3 caliAccel[10]; //x+ x- y+ y- z+ z- �ټ���4������Ƕ�
uint8_t caliAccCnt = 0;

static CL_BOOL Calibrate(void)
{
    static uint64_t lastTime = 0;
    Vector3 acc;

    if(TimeElapsed(lastTime) > 10)
    {
        SetToCurTime(&lastTime);

        BMI160_GetData(&acc, CL_NULL);
        if(IsAccelStable(&acc, &acc))
        {
            Log("stable\r\n");
        }
        else
        {
            Log("not stable\r\n");
        }

    }



    return CL_FALSE;
}

typedef enum
{
    IDLE = 0,
    ATT_CALC,
    CALIBRATE,
} Attitude_Task_t;
static Attitude_Task_t task = IDLE;

void Attitude_Process(void)
{
    switch (task)
    {
        case IDLE:
            Calibrate();
            break;
        case ATT_CALC:
            break;
        case CALIBRATE:
            break;
    }
}









