#include "attitude.h"
#include "sensors.h"
#include "mathex.h"
#include "sys_time.h"
#include "cl_queue.h"


char printBuff[128];

static Vector3 gyroStaticError; //陀螺仪静态偏差


//-------------------------------传感器稳定判断-----------------------------------
#define STABLE_SAMPLE_NUM    100
CL_QUEUE_DEF_INIT(stable_q, STABLE_SAMPLE_NUM, Vector3, static);

//清空stable队列记录
CL_STATIC_INLINE void ResetStable()
{
    CL_QueueClear(&stable_q);
}
//判断sample数据是否stable
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
        //已采样100次

        //计算出平均值
        CL_QUEUE_FOR_EACH(&stable_q, v, Vector3)
        {
            Vector3_Add(&average, v, &average);
        }
        Vector3_Scale(&average, (1.0f / STABLE_SAMPLE_NUM), &average);

        //判断每次采样和平均值的差值
        CL_QUEUE_FOR_EACH(&stable_q, v, Vector3)
        {
            Vector3_Subtract(&average, v, &diff);
            float error = Vector3_SqrMagnitude(&diff);
            if(error >= tolerance)
            {
                //如果任意一个差值过大,则还没稳定
//                Log("diff: %.3f\r\n", error);
                return CL_FALSE;
            }
        }

        //所有采样都非常接近,则已经稳定
        out->x = average.x;
        out->y = average.y;
        out->z = average.z;
        return CL_TRUE;
    }

    return CL_FALSE;
}
//*******************************************************************

//-----------------------------校准流程-----------------------------------------------
#define caliAccSampleNum  6  //加速度采样次数
Vector3 caliAccRecord[caliAccSampleNum]; //采样记录
uint8_t caliAccSampleCnt = 0;    //采样计数
//需要采样的方向
const Vector3 caliAccDirs[caliAccSampleNum] = { {1, 0, 0},      //x+
    {-1, 0, 0},     //x-
    {0, 1, 0},      //y+
    {0, -1, 0},     //y-
    {0, 0, 1},      //z+
    {0, 0, -1},     //z-
};
//采样的方向提示
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

//开始加速度校准
CL_STATIC_INLINE void StartAccCali(void)
{
    Log("校准加速度\r\n");
    caliState = CALI_ACC;
    caliAccSampleCnt = 0;
    ResetStable();
    Log("开始采样: %s\r\n", caliDirTips[caliAccSampleCnt]);
}

//开始陀螺仪校准
CL_STATIC_INLINE void StartGryoCali(void)
{
    Log("校准陀螺仪\r\n");
    caliState = CALI_GYRO;
    ResetStable();
    Log("开始采样,保持sensor静止\r\n");
}


CL_STATIC_INLINE void StartCalibrate(void)
{
    Log("准备校准\r\n");
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
        {   //校准acc
            Vector3 acc;
            BMI160_GetData(&acc, CL_NULL);
            if(IsSensorStable(&acc, &acc, ACCEL_STABLE_THRESHOLD))
            {
                cos = Vector3_Cos(&caliAccDirs[caliAccSampleCnt], &acc);
                if(FLOAT_NEAR(cos, 1.0f, 0.05f))
                {
                    //采样完成
                    caliAccRecord[caliAccSampleCnt] = acc;
                    Log("%s 采样完成\r\n", caliDirTips[caliAccSampleCnt]);


                    ResetStable();
                    caliAccSampleCnt++;
                    if(caliAccSampleCnt < caliAccSampleNum)
                    {
                        //采样下一个方向
                        Log("开始采样: %s\r\n", caliDirTips[caliAccSampleCnt]);
                    }
                    else
                    {
                        //采样完成,计算校准参数
                        //TODO 校准算法
                        Log("---------------加速度校准完成-------------\r\n");
                        for(int i = 0; i < caliAccSampleNum; i++)
                        {
                            Log("%s: %s\r\n", caliDirTips[i], Vector3_ToString(&caliAccRecord[i], printBuff));
                        }
                        Log("*****************************************\r\n");
                        StartGryoCali(); //开始校准陀螺仪
                        return CL_FALSE;
                    }
                }
            }
        }
        else if(caliState == CALI_GYRO)
        {   //校准gyro
            Vector3 gyro;
            BMI160_GetData(CL_NULL, &gyro);
            if(IsSensorStable(&gyro, &gyroStaticError, GYRO_STABLE_THRESHOLD))
            {
                Log("---------------陀螺仪校准完成-------------\r\n");
                Log("静态偏差: %s\r\n", Vector3_ToString(&gyroStaticError, printBuff));
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
        //打印加速度
        Log("acc: %s; ", Vector3_ToString(&acc, printBuff));
        //打印角速度
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
                Log("校准完成\r\n");
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






