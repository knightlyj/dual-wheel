#pragma once
#include "cl_common.h"

extern uint64_t g_sysTotalTime; //ϵͳʱ��,��λ����,���������

//����ϵͳʱ��,������ü��
CL_STATIC_INLINE void UpdateSysTime(uint16_t interval)
{
    g_sysTotalTime += interval;
}


//��preTime�����ھ�����ʱ��
CL_STATIC_INLINE uint64_t TimeElapsed(uint64_t preTime)
{
    return g_sysTotalTime - preTime;
}

//*pTime����Ϊ��ǰʱ��
CL_STATIC_INLINE void SetToCurTime(uint64_t* pTime)
{
    *pTime = g_sysTotalTime;
}


extern void DelayMs(uint16_t ms);
extern void DelayUs(uint16_t us);

