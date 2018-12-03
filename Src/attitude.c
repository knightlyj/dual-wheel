#include "attitude.h"
#include "sensors.h"
#include "mathex.h"
#include "sys_time.h"
#include "cl_queue.h"


char printBuff[128];

static Vector3 gyroStaticError; //�����Ǿ�̬ƫ��


//-------------------------------�������ȶ��ж�-----------------------------------
#define STABLE_SAMPLE_NUM    100
CL_QUEUE_DEF_INIT(stable_q, STABLE_SAMPLE_NUM, Vector3, static);

//���stable���м�¼
CL_STATIC_INLINE void ResetStable()
{
    CL_QueueClear(&stable_q);
}
//�ж�sample�����Ƿ�stable
static CL_BOOL IsSensorStable(Vector3* sample, Vector3* out, float tolerance)
{
    Vector3* v;
    Vector3 average = {0,0,0};
    Vector3 diff;

    if(CL_QueueFull(&stable_q))
    {
        CL_QueuePoll(&stable_q, &diff);
    }

    CL_QueueAdd(&stable_q, sample);

    if(CL_QueueFull(&stable_q))
    {
        //�Ѳ���100��

        //�����ƽ��ֵ
        CL_QUEUE_FOR_EACH(&stable_q, v, Vector3)
        {
            Vector3_Add(&average, v, &average);
        }
        Vector3_Scale(&average, (1.0f / STABLE_SAMPLE_NUM), &average);

        //�ж�ÿ�β�����ƽ��ֵ�Ĳ�ֵ
        CL_QUEUE_FOR_EACH(&stable_q, v, Vector3)
        {
            Vector3_Subtract(&average, v, &diff);
            float error = Vector3_SqrMagnitude(&diff);
            if(error >= tolerance)
            {
                //�������һ����ֵ����,��û�ȶ�
//                Log("diff: %.3f\r\n", error);
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
//*******************************************************************

//-----------------------------У׼����-----------------------------------------------
#define caliAccSampleNum  6  //���ٶȲ�������
Vector3 caliAccRecord[caliAccSampleNum]; //������¼
uint8_t caliAccSampleCnt = 0;    //��������
//��Ҫ�����ķ���
const Vector3 caliAccDirs[caliAccSampleNum] = { {1, 0, 0},      //x+
    {-1, 0, 0},     //x-
    {0, 1, 0},      //y+
    {0, -1, 0},     //y-
    {0, 0, 1},      //z+
    {0, 0, -1},     //z-
};
//�����ķ�����ʾ
const char* caliDirTips[] = {  "x+",
                               "x-",
                               "y+",
                               "y-",
                               "z+",
                               "z-",
                            };

typedef enum
{
    CALI_ACC,
    CALI_GYRO,
} Calibrate_State_t;
Calibrate_State_t caliState = CALI_ACC;

//��ʼ���ٶ�У׼
CL_STATIC_INLINE void StartAccCali(void)
{
    Log("У׼���ٶ�\r\n");
    caliState = CALI_ACC;
    caliAccSampleCnt = 0;
    ResetStable();
    Log("��ʼ����: %s\r\n", caliDirTips[caliAccSampleCnt]);
}

//��ʼ������У׼
CL_STATIC_INLINE void StartGryoCali(void)
{
    Log("У׼������\r\n");
    caliState = CALI_GYRO;
    ResetStable();
    Log("��ʼ����,����sensor��ֹ\r\n");
}


CL_STATIC_INLINE void StartCalibrate(void)
{
    Log("׼��У׼\r\n");
    StartAccCali(); 
//    StartGryoCali();
}


#define ACCEL_STABLE_THRESHOLD     (0.05f)
#define GYRO_STABLE_THRESHOLD      (2.0f)

static CL_BOOL Calibrate(void)
{
    static uint64_t lastTime = 0;
    float cos;

    if(TimeElapsed(lastTime) > 10)
    {
        SetToCurTime(&lastTime);
        if(caliState == CALI_ACC)
        {   //У׼acc
            Vector3 acc;
            BMI160_GetData(&acc, CL_NULL);
            if(IsSensorStable(&acc, &acc, ACCEL_STABLE_THRESHOLD))
            {
                cos = Vector3_Cos(&caliAccDirs[caliAccSampleCnt], &acc);
                if(FLOAT_NEAR(cos, 1.0f, 0.05f))
                {
                    //�������
                    caliAccRecord[caliAccSampleCnt] = acc;
                    Log("%s �������\r\n", caliDirTips[caliAccSampleCnt]);


                    ResetStable();
                    caliAccSampleCnt++;
                    if(caliAccSampleCnt < caliAccSampleNum)
                    {
                        //������һ������
                        Log("��ʼ����: %s\r\n", caliDirTips[caliAccSampleCnt]);
                    }
                    else
                    {
                        //�������,����У׼����
                        //TODO У׼�㷨
                        Log("---------------���ٶ�У׼���-------------\r\n");
                        for(int i = 0; i < caliAccSampleNum; i++)
                        {
                            Log("%s: %s\r\n", caliDirTips[i], Vector3_ToString(&caliAccRecord[i], printBuff));
                        }
                        Log("*****************************************\r\n");
                        StartGryoCali(); //��ʼУ׼������
                        return CL_FALSE;
                    }
                }
            }
        }
        else if(caliState == CALI_GYRO)
        {   //У׼gyro
            Vector3 gyro;
            BMI160_GetData(CL_NULL, &gyro);
            if(IsSensorStable(&gyro, &gyroStaticError, GYRO_STABLE_THRESHOLD))
            {
                Log("---------------������У׼���-------------\r\n");
                Log("��̬ƫ��: %s\r\n", Vector3_ToString(&gyroStaticError, printBuff));
                Log("*****************************************\r\n");
                return CL_TRUE;
            }
        }
    }

    return CL_FALSE;
}
//************************************************************************************


static void PrintSensorData(void)
{
    uint64_t lastPrintTime;
    Vector3 acc, gyro;
    if(TimeElapsed(lastPrintTime) > 500)
    {
        SetToCurTime(&lastPrintTime);
        BMI160_GetData(&acc, &gyro);
        //��ӡ���ٶ�
        Log("acc: %s; ", Vector3_ToString(&acc, printBuff));
        //��ӡ���ٶ�
        Log("gyro: %s\r\n", Vector3_ToString(&gyro, printBuff));
    }
}


typedef enum
{
    IDLE = 0,
    ATT_CALC,
    CALIBRATE,
    PRINT_SENSOR,
} Attitude_Task_t;
static Attitude_Task_t task = IDLE;

void Attitude_Process(void)
{
    switch (task)
    {
        case IDLE:
            break;
        case ATT_CALC:

            break;
        case CALIBRATE:
            if(Calibrate() == CL_TRUE)
            {
                Log("У׼���\r\n");
                task = IDLE;
            }
            break;
        case PRINT_SENSOR:
            PrintSensorData();
            break;
    }
}


void Attitude_RecvCmd(char c)
{
    switch (c)
    {
        case 'c':
            task = CALIBRATE;
            StartCalibrate();
            break;
        case 'p':
            task = PRINT_SENSOR;
            break;
        case 'a':
            task = ATT_CALC;
            break;
        case 'i':
            task = IDLE;
            break;
    }
}






